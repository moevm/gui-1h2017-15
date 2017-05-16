#ifndef CONNECTIONLISTENER_H
#define CONNECTIONLISTENER_H

#include <QString>


class ConnectionListener
{
public:
    ConnectionListener();

    /**
     * Response after connection attempt arrived
     *
     * @brief connected
     *
     * @param success - success flag
     * @param message - error or success messages
     */
    virtual void connected(bool success, QString message) = 0;

    /**
     * Response after sign in action arrived
     *
     * @brief loggedIn
     *
     * @param success - success flag
     * @param message - error or success messages
     */
    virtual void loggedIn(bool success, QString message) = 0;

    /**
     * Response after message was sent to recipient
     *
     * @brief messageSent
     *
     * @param success - success flag
     * @param message - error or success messages
     */
    virtual void messageSent(bool success, QString message) = 0;
};

#endif // CONNECTIONLISTENER_H
