#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QSslSocket>;

/*
 * AuntificationManager
 * 
 * Takes care of all auntification things
 * 
 * @author Popov Artem
 */
class ConnectionManager
{
public:
    static ConnectionManager* getInstance();

    /**
     * Some initialization things to do
     *
     * @brief init
     * @return success flag
     */
    bool init();

    /**
     * Connect to specified server with ssl
     *
     * @brief connectToSslServer
     * @param host
     * @param port
     * @return success flag
     */
    bool connectToServer(QString &host, int port);

    /**
     * Sign in on server.
     *
     * Maybe should do something with security.
     *
     * @brief doLogin
     * @param username
     * @param password
     * @return
     */
    bool doLogin(QString &username, QString &password);

private:
    ConnectionManager();

private:
    static ConnectionManager *instance;

    // mail server connection socket
    QSslSocket *connectionSocket;


};

#endif // CONNECTIONMANAGER_H
