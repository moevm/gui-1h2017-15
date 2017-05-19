#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <msgbody.h>

class Message
{
private:
    QString theme;
    QString title;
    msgBody bodyText;
    msgBody bodyHTML;
    QDateTime dateTime;
    QString sender;
    QString receiver;


public:
    Message();
    Message(QString theme, QString title, QString a, QString sender, QString receiver, QDateTime dateTime);

    Message(QString theme, QString title, msgBody bodyText, msgBody bodyHTML, QString sender, QString receiver, QDateTime dateTime);
    QString getMessage() const;
    QString getTheme() const;
    QString getTitle() const;
    msgBody getBodyText() const;
    msgBody getBodyHTML() const;

    QString getDateTime() const;
    QString getSender() const;
    QString getReceiver() const;



    void setTheme(QString theme);
    void setTitle(QString title);
    void setBodyText(msgBody bodyText);
    void setBodyHTML(msgBody bodyHTML);

    void setDateTime(QDateTime dateTime);
    void setSender(QString sender);
    void setReceiver(QString receiver);


};

#endif // MESSAGE_H
