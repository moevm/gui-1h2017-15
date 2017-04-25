#ifndef MAILBOX_H
#define MAILBOX_H

#include <QMainWindow>

namespace Ui {
class MailBox;
}

class MailBox : public QMainWindow
{
    Q_OBJECT

public:
    explicit MailBox(QWidget *parent = 0);
    ~MailBox();

private:
    Ui::MailBox *ui;

    void changeSize();
    void resizeEvent(QResizeEvent *event);
};

#endif // MAILBOX_H
