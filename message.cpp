#include "message.h"

Message::Message(QString theme, QString title, msgBody bodyText, msgBody bodyHTML, QString sender, QString receiver, QDateTime dateTime)
    : theme(theme), title(title), bodyText(bodyText), bodyHTML(bodyHTML), sender(sender), receiver(receiver), dateTime(dateTime)
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

msgBody Message::getBodyText() const {
    return bodyText;
}
msgBody Message::getBodyHTML() const {
    return bodyHTML;
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

void Message::setBodyText(msgBody body) {
    this->bodyText = body;
}
void Message::setBodyHTML(msgBody body) {
    this->bodyHTML = body;
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
