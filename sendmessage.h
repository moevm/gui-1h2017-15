#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QMainWindow>
#include "message.h"
#include <QDateTime>
#include <connectionlistener.h>

namespace Ui {
class SendMessage;
}

class SendMessage : public QMainWindow, public ConnectionListener
{
    Q_OBJECT

public:
    explicit SendMessage(QWidget *parent = 0);
    SendMessage(QString name);
    ~SendMessage();

public slots:
    void onSendClicked();

private:
    Ui::SendMessage *ui;
    QString sender;
    void changeSize();
    void resizeEvent(QResizeEvent *event);

    // ConnectionListener interface
public:
    void connected(bool success, QString message);
    void loggedIn(bool success, QString message);
    void messageSent(bool success, QString message);
};

#endif // SENDMESSAGE_H
