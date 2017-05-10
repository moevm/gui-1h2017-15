#ifndef MYPARSER_H
#define MYPARSER_H

#include <message.h>
#include <QDebug>

class MyParser
{
public:
    MyParser();
    Message parseMail(QString input);
private:
    QString theme;
    QString title;
    QString body;
    QDateTime dateTime;
    QString sender;
    QString receiver;
};

#endif // MYPARSER_H
