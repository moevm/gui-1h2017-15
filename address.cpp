#include "address.h"

Address::Address()
{

}

unsigned Address::getPort() const
{
    return port;
}

void Address::setPort(const unsigned &value)
{
    port = value;
}

QString Address::getHost() const
{
    return host;
}

void Address::setHost(const QString &value)
{
    host = value;
}
