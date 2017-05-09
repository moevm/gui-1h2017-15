#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QMainWindow>
#include "message.h"
#include <QDateTime>

namespace Ui {
class SendMessage;
}

class SendMessage : public QMainWindow
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
};

#endif // SENDMESSAGE_H
