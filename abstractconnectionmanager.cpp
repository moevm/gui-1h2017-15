#include "abstractconnectionmanager.h"


AbstractConnectionManager::AbstractConnectionManager(ConnectionListener *listener, Address serverAddress) :
    serverAddr(serverAddress), connectionAvailable(false)
{
    connectionListeners = QVector<ConnectionListener*>(0);
    connectionListeners.append(listener);
}

void AbstractConnectionManager::addConnectionListener(ConnectionListener *listener)
{
    connectionListeners.append(listener);
}

Address AbstractConnectionManager::getConnectionAddress()
{
    return serverAddr;
}

bool AbstractConnectionManager::isConnectionAvailable()
{
    return connectionAvailable;
}


