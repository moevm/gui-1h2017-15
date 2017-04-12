#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>

/**
 * Some internet address representation
 *
 * maybe there are such class in qt, but
 * isn't it funny to write such things from scrath?
 *
 * @brief The Address class
 */
class Address
{
private:
    QString host;
    unsigned port;

public:
    Address(QString host, unsigned port) : host(host), port(port) {

    }

    QString getHost() const {
        return host;
    }

    unsigned getPort() const {
        return port;
    }
};

#endif // ADDRESS_H
