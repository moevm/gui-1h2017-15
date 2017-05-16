#ifndef MAILBOX_H
#define MAILBOX_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <message.h>
#include <QScrollArea>
#include <QListWidget>
#include <QListWidgetItem>
#include <sendmessage.h>

namespace Ui {
class MailBox;
}

class MailBox : public QMainWindow
{
    Q_OBJECT

public:
    explicit MailBox(QWidget *parent = 0);
    ~MailBox();
    void addMessage(QList<Message> *list, QListWidget *listWidget);
    void setName(QString name);
    void setList(QList<Message> *list);
    void initWidget();

public slots:
    void onInboxClicked();
    void onOutboxClicked();
    void onLogOutClicked();
    void onWriteMessageClicked();

signals:
    void firstWindow();

private:
    Ui::MailBox *ui;
    QScrollArea *window;
    QListWidget *listWidget;
    QLayout *layoutVert;
    QString name;
    QList<Message> *listRec;

    void clearLayout(QLayout * layout);
    void setIcons();
    void changeSize();
    void resizeEvent(QResizeEvent *event);
};

#endif // MAILBOX_H
