#include "message.h"

Message::Message(QString theme, QString title, QString body, QString sender, QString receiver, QDateTime dateTime)
    : theme(theme), title(title), body(body), sender(sender), receiver(receiver), dateTime(dateTime)
{
}

Message::Message(){

}

QString Message::getMessage() const{
}

QString Message::getTheme() const {
    return theme;
}

QString Message::getTitle() const {
    return title;
}

QString Message::getBody() const {
    return body;
}

QString Message::getDateTime() const {
    QString str;
    str = dateTime.toString(Qt::RFC2822Date);
    return str;
}

QString Message::getSender() const {
    return sender;
}

QString Message::getReceiver() const {
    return receiver;
}

void Message::setTheme(QString theme) {
    this->theme = theme;
}

void Message::setTitle(QString title) {
    this->title = title;
}

void Message::setBody(QString body) {
    this->body = body;
}

void Message::setDateTime(QDateTime dateTime) {
    this->dateTime = dateTime;
}

void Message::setSender(QString sender) {
    this->sender = sender;
}

void Message::setReceiver(QString receiver) {
    this->receiver = receiver;
}
