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
    QString receiver,sender,theme;
};

#endif // MYPARSER_H
