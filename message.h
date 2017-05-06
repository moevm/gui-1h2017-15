#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

class Message
{
private:
    QString theme;
    QString title;
    QString body;
    QDateTime dateTime;
    QString sender;
    QString receiver;

public:
    Message();
    Message(QString theme, QString title, QString body, QString sender, QString receiver, QDateTime dateTime);
    QString getMessage() const;
    QString getTheme() const;
    QString getTitle() const;
    QString getBody() const;
    QString getDateTime() const;
    QString getSender() const;
    QString getReceiver() const;
    void setTheme(QString theme);
    void setTitle(QString title);
    void setBody(QString body);
    void setDateTime(QDateTime dateTime);
    void setSender(QString sender);
    void setReceiver(QString receiver);

};

#endif // MESSAGE_H
