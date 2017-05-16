#ifndef MYPARSER_H
#define MYPARSER_H

#include <message.h>
#include <msgbody.h>
#include <QDebug>
#include <QList>

class MyParser
{
public:
    MyParser();
    Message parseMail(QString input);
    QList<msgBody> parseBody(QString input);
private:
    QString theme;
    QString title;
    QString body;
    QDateTime dateTime;
    QString sender;
    QString receiver;
    QString contenttype;
    QString utf;
    QString base;


};

#endif // MYPARSER_H
