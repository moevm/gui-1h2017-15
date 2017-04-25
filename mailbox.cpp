#include "mailbox.h"
#include "ui_mailbox.h"

MailBox::MailBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MailBox)
{
    ui->setupUi(this);
    window = new QWidget(this);
    window->setGeometry(90, 50, 300, 600);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::lightGray);
    window->setAutoFillBackground(true);
    window->setPalette(Pal);

    /*Сейчас пойдет заглушка для списка сообщений*/
    Message mes1("HELLO", "123", "sf", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes2("HELLO", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    QList<Message> *list = new QList<Message>;
    list->append(mes1);
    list->append(mes2);

    listMessage = new QVBoxLayout(this);
    addMessage(list);
    window->setLayout(listMessage);
    setIcons();
}

MailBox::~MailBox()
{
    delete ui;
}
void MailBox::setIcons()
{
    ui->inbox->setIcon(QIcon("../gui-1h2017-15/image/inbox.png"));
    ui->inbox->setIconSize(QSize(65,65));
    ui->outbox->setIcon(QIcon("../gui-1h2017-15/image/outbox.png"));
    ui->outbox->setIconSize(QSize(65,65));
}

void MailBox::addMessage(QList<Message> *list) {
    for (int i = 0; i < list->size(); ++i) {
        QLabel *title = new QLabel(this);
        title->setText(list->at(i).getTitle());
        title->setGeometry(100, 30*i,50,20 );
        listMessage->addWidget(title);
    }

}

void MailBox::resizeEvent(QResizeEvent *event){
    this->changeSize();
}

void MailBox::changeSize()
{
    ui->logout->setGeometry(this->size().width()-75,0, 75, 31);
    ui->line->setGeometry(0, 20,this->size().width()-20, 20);
    ui->line_2->setGeometry(83, 30, 20, this->size().height());
    window->setGeometry(90, 50, this->size().width()/2.5, this->size().height());
}
