#include "connectionManager.h"

ConnectionManager *ConnectionManager::instance;

ConnectionManager *ConnectionManager::getInstance()
{
    if (instance == nullptr) {
        instance = new ConnectionManager;
    }

    return instance;
}

bool ConnectionManager::init()
{
    // do initialization
}

bool ConnectionManager::connectToServer(QString &host, int port)
{
    int timeout = 1000;

    if (connectionSocket == nullptr) {
       connectionSocket = new QSslSocket;
    }

    connectionSocket->connectToHostEncrypted(host, port);

    if (!connectionSocket->waitForConnected(timeout)) {
         qDebug() << connectionSocket->errorString();
         return false;
     }

    return true;
}

bool ConnectionManager::doLogin(QString &username, QString &password)
{
    if (connectionSocket == nullptr) {
        qDebug() << "Connect to server first";
        return false;
    }

    return true;
}

ConnectionManager::ConnectionManager() : connectionSocket(nullptr)
{

}
