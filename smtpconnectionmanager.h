#ifndef SMTPCONNECTIONMANAGER_H
#define SMTPCONNECTIONMANAGER_H

#include <QString>
#include <QSslSocket>

#include <abstractconnectionmanager.h>
#include <Pop3Client.h>
#include <address.h>
#include <message.h>

/**
 * Working with smtp servers
 * Singleton
 *
 * @brief The SmtpConnectionManager class
 */
class SmtpConnectionManager : public AbstractConnectionManager
{
    Q_OBJECT

private:
    QSslSocket *sslSocket;
    QTextStream *streamToServer;

    Message message;
    QString messageText;

    static SmtpConnectionManager *instance;

    QString lastResponse;

    enum states{INIT, CONNECTED, SIGNED_IN,
                HANDSHAKE, AUTH, WAITING_AUTH_REQUEST,
                WAITING_FOR_USERNAME, WAITING_FOR_PASSWORD,
               WAITING_FOR_MAIL, CLOSING, SENDER_SENT, RECIPIENT_SENT, MESSAGE_SENT, MAIL_SENT};

    int state;

    QString user;
    QString password;

public:
    // AbstractConnectionManager interface
    void doConnect();
    void signIn(QString username, QString password);
    void sendMessage(Message message);

    static SmtpConnectionManager  * createInstance(ConnectionListener *connectionListener, Address serverAddress);
    static SmtpConnectionManager  * getInstance();

private:
    /**
     * Create new Smtp Manager with specified listener
     *
     * @param listener - listen to connection events such establishing
     * connection, log on, and so on
     */
    SmtpConnectionManager(ConnectionListener *connectionListener, Address serverAddress);

    void sendConnectEventToAll(bool success, QString message);
    void sendLoggedInEventToAll(bool success, QString message);
    void sendMessageSentEventToAll(bool success, QString message);

    QString storeNextResponseAndGetCode();
    // handshake with the server to get ready to next movements
    void doHandshake();
    void switchToEncryptedMode();
    void doAuth();
    void sendUsername();
    void sendPassword();
    void resetConnection();


    ~SmtpConnectionManager();

private slots:
    void errorOccured(QAbstractSocket::SocketError);
    void stateChanged(QAbstractSocket::SocketState);
    void connected();
    void readyRead();
    void disconnected();
};

#endif // SMTPCONNECTIONMANAGER_H
