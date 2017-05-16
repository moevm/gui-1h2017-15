#include "smtpconnectionmanager.h"
#include <iostream>

using namespace std;

SmtpConnectionManager * SmtpConnectionManager::instance;

SmtpConnectionManager::SmtpConnectionManager(ConnectionListener *connectionListener, Address serverAddress) :
    AbstractConnectionManager(connectionListener, serverAddress), state(INIT), user(), password()
{
    sslSocket = new QSslSocket();
    streamToServer = new QTextStream(sslSocket);

    connect(sslSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorOccured(QAbstractSocket::SocketError)));
    connect(sslSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(sslSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(sslSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(sslSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));

}

void SmtpConnectionManager::sendConnectEventToAll(bool success, QString message)
{
    for (int i = 0; i < connectionListeners.size(); i++) {
        connectionListeners.at(i)->connected(success, message);
    }
}

void SmtpConnectionManager::sendLoggedInEventToAll(bool success, QString message)
{
    for (int i = 0; i < connectionListeners.size(); i++) {
        connectionListeners.at(i)->loggedIn(success, message);
    }
}

void SmtpConnectionManager::sendMessageSentEventToAll(bool success, QString message)
{
    for (int i = 0; i < connectionListeners.size(); i++) {
        connectionListeners.at(i)->messageSent(success, message);
    }
}

void SmtpConnectionManager::doConnect()
{
    state = INIT;
    sslSocket->connectToHostEncrypted(serverAddr.getHost(), serverAddr.getPort());

    connectionAvailable = true;
}

void SmtpConnectionManager::signIn(QString username, QString pass)
{
    user = username;
    password = pass;

    if (!connectionAvailable) {
        doConnect();
    } else {
        doAuth();
        state = WAITING_FOR_USERNAME;
    }

    /**
    if (state != WAITING_AUTH_REQUEST) {
        qDebug() << "trying to perform login, but connection manager is not ready!" << endl;
    } else {
        user = username;
        password = password;

        state = WAITING_FOR_USERNAME;
    }*/
}

void SmtpConnectionManager::sendMessage(Message messageStruct)
{
    message = messageStruct;

    messageText = "To: " + messageStruct.getReceiver() + "\n";
    messageText.append("From: " + messageStruct.getSender() + "\n");
    messageText.append("Subject: " + messageStruct.getTheme() + "\n");
    messageText.append(messageStruct.getBodyText().getMessage());

    messageText.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
    messageText.replace( QString::fromLatin1( "\r\n.\r\n" ),
    QString::fromLatin1( "\r\n..\r\n" ) );
    state = SENDER_SENT;

    qDebug() << "MAIL FROM:<" << messageStruct.getSender() << ">";
    *streamToServer << "MAIL FROM:<" <<  messageStruct.getSender() << ">\r\n";
    streamToServer->flush();
}

SmtpConnectionManager *SmtpConnectionManager::getInstance()
{
    if (instance == nullptr) {
        cerr << "Cannot get instance before initialization!" << endl;
        return nullptr;
    }

    return instance;
}

SmtpConnectionManager *SmtpConnectionManager::createInstance(ConnectionListener *connListener, Address serverAddr)
{
    if (instance == nullptr) {
        instance = new SmtpConnectionManager(connListener, serverAddr);
    }

    return instance;
}

//Ssl socket slots

void SmtpConnectionManager::errorOccured(QAbstractSocket::SocketError error)
{
    qDebug() << "Error with connection: " << error << endl;

    if (state == INIT) {
        sendConnectEventToAll(false, "Can't connect to server!");
    }
}

void SmtpConnectionManager::stateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << "State changed: " << state << endl;
}

void SmtpConnectionManager::connected()
{
    qDebug() << "Connected" << endl;
}

void SmtpConnectionManager::readyRead()
{
    qDebug() << "Ready to read";

    lastResponse = " ";

    // read SMTP message

    QString responseCode = storeNextResponseAndGetCode();

    if (state == INIT && responseCode == "220") {
        sendConnectEventToAll(true, lastResponse);
        doHandshake();
        state = HANDSHAKE;
    } else if (state == HANDSHAKE && responseCode == "250") {
        qDebug() << "successfully handshaked" << endl;

        switchToEncryptedMode();

        // encrypted handshake now
        doHandshake();

        state = AUTH;
    } else if (state == AUTH && responseCode == "250") {
        doAuth();

        state = WAITING_FOR_USERNAME;
    } else if (state == WAITING_FOR_USERNAME && responseCode == "334") {

        sendUsername();

        state = WAITING_FOR_PASSWORD;
    } else if (state == WAITING_FOR_PASSWORD && responseCode == "334") {
        sendPassword();

        state = WAITING_FOR_MAIL;
    } else if (state == WAITING_FOR_MAIL && responseCode == "235") {
        sendLoggedInEventToAll(true, "success");
    } else if ( state == SENDER_SENT && responseCode == "250" )
    {
        //Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        *streamToServer << "RCPT TO:<" << message.getReceiver() << ">\r\n"; //r
        streamToServer->flush();
        state = RECIPIENT_SENT;
    }
    else if ( state == RECIPIENT_SENT && responseCode == "250" )
    {
        *streamToServer << "DATA\r\n";
        streamToServer->flush();
        state = MESSAGE_SENT;
    }
    else if ( state == MESSAGE_SENT && responseCode == "354" )
    {
        *streamToServer << messageText << "\r\n.\r\n";
        streamToServer->flush();
    }
    else if ( state == MESSAGE_SENT && responseCode == "250" )
    {
        sendMessageSentEventToAll(true, "Message Sent");
    } else if (responseCode == "535") {
        sendLoggedInEventToAll(false, "Username and password not accepted");
        resetConnection();
    } else if (state == CLOSING) {
        state = INIT;
        connectionAvailable = false;

        qDebug() << "Connection closed" << endl;
        return;
    }
}

QString SmtpConnectionManager::storeNextResponseAndGetCode()
{
    QString responseLine;
    do
    {
        responseLine = sslSocket->readLine();
        lastResponse += responseLine;
    }
    while (sslSocket->canReadLine() && responseLine[3] != ' ' );

    responseLine.truncate(3);

    qDebug() << "Server response code:" <<  responseLine;
    qDebug() << "Server response: " << lastResponse;

    return responseLine;
}

void SmtpConnectionManager::switchToEncryptedMode()
{
    //TODO remove magic number
    int timeout = 3000;

    sslSocket->startClientEncryption();
    if(!sslSocket->waitForEncrypted(timeout))
    {
        qDebug() << sslSocket->errorString();
    }
}

void SmtpConnectionManager::doAuth()
{
    // Trying AUTH
    qDebug() << "Auntification attempt";
    *streamToServer << "AUTH LOGIN" << "\r\n";
    streamToServer->flush();
}

void SmtpConnectionManager::sendUsername()
{
    //Trying User
    qDebug() << "Sending username";
    //GMAIL is using XOAUTH2 protocol, which basically means that password and username has to be sent in base64 coding
    //https://developers.google.com/gmail/xoauth2_protocol
    *streamToServer << QByteArray().append(user).toBase64()  << "\r\n";
    streamToServer->flush();
}

void SmtpConnectionManager::sendPassword()
{
    //Trying pass
    qDebug() << "Sending password";
    *streamToServer << QByteArray().append(password).toBase64() << "\r\n";
    streamToServer->flush();
}

void SmtpConnectionManager::resetConnection()
{
    *streamToServer << "QUIT\r\n";
    streamToServer->flush();

    state = CLOSING;
}

void SmtpConnectionManager::doHandshake()
{
    qDebug() << "doing handshake" << endl;

    *streamToServer << "EHLO localhost" <<"\r\n";
    streamToServer->flush();
}

SmtpConnectionManager::~SmtpConnectionManager()
{
    delete sslSocket;
    delete streamToServer;
}

void SmtpConnectionManager::disconnected()
{
    qDebug() << "Disconnected" << endl;
    qDebug() << "reason: " << sslSocket->errorString() << endl;
}
