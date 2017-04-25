#ifndef MAILBOX_H
#define MAILBOX_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <message.h>

namespace Ui {
class MailBox;
}

class MailBox : public QMainWindow
{
    Q_OBJECT

public:
    explicit MailBox(QWidget *parent = 0);
    ~MailBox();
    void addMessage(QList<Message> *list);

private:
    Ui::MailBox *ui;
    QVBoxLayout *listMessage;
    QWidget *window;

    void setIcons();
    void changeSize();
    void resizeEvent(QResizeEvent *event);
};

#endif // MAILBOX_H
