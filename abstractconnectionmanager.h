#ifndef ABSTRACTCONNECTIONMANAGER_H
#define ABSTRACTCONNECTIONMANAGER_H

#include <QVector>
#include <QObject>

#include <address.h>
#include <connectionlistener.h>

/**
 * ConnectManager
 *
 * Handles all connection related things
 * such auntification, connection handling and etc
 *
 */
class AbstractConnectionManager : public QObject
{

protected:
    /**
     * Parameters of current connection
     */
    Address serverAddr;

    bool connectionAvailable;

    QVector<ConnectionListener*> connectionListeners;

public:

     /**
      * Create new Manager with specified listener
      *
      * @brief AbstractConnectionManager
      * @param listener - listen to connection events such establishing
      * connection, log on, and so on
      */
     AbstractConnectionManager(ConnectionListener *listener, Address address);

     void addConnectionListener(ConnectionListener *listener);

     /**
      * Establish connection
      *
      * @brief connect
      */
     virtual void doConnect() = 0;

     /**
      * Perform log in on the server
      *
      * @param username
      * @param password
      */
     virtual void signIn(QString username, QString password) = 0;

     Address getConnectionAddress();

     bool isConnectionAvailable();

};

#endif // ABSTRACTCONNECTIONMANAGER_H
