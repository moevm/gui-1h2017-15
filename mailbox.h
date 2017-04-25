#ifndef MAILBOX_H
#define MAILBOX_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <message.h>
#include <QScrollArea>
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class MailBox;
}

class MailBox : public QMainWindow
{
    Q_OBJECT

public:
    explicit MailBox(QWidget *parent = 0);
    ~MailBox();
    void addMessage(QList<Message> *list, QListWidget *lstWgt);

public slots:
    void onInboxClicked();
    void onOutboxClicked();

private:
    Ui::MailBox *ui;
    QScrollArea *window;
    QListWidget* listWidget;
    QLayout* layoutVert;

    void clearLayout(QLayout * layout);
    void setIcons();
    void changeSize();
    void resizeEvent(QResizeEvent *event);
};

#endif // MAILBOX_H
