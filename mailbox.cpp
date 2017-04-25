#include "mailbox.h"
#include "ui_mailbox.h"

MailBox::MailBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MailBox)
{
    ui->setupUi(this);
    connect( ui->inbox, SIGNAL( clicked() ), SLOT( onInboxClicked() ) );
    connect( ui->outbox, SIGNAL( clicked() ), SLOT( onOutboxClicked() ) );

    window = new QScrollArea(this);
    window->setGeometry(90, 50, 300, 500);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::lightGray);
    window->setAutoFillBackground(true);
    window->setPalette(Pal);

    /*Сейчас пойдет заглушка для списка сообщений*/
    Message mes1("HELLO", "123", "sf", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes2("HELLO2", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes3("HELLO3", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes4("HELLO4", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes5("HELLO5", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes6("HELLO6", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    QList<Message> *list = new QList<Message>;
    list->append(mes1);
    list->append(mes2);
    list->append(mes3);
    list->append(mes4);
    list->append(mes5);
    list->append(mes6);

    listWidget = new QListWidget;
    layoutVert = new QVBoxLayout;
    layoutVert->addWidget( listWidget );
    window->setLayout( layoutVert );
    addMessage(list,listWidget);

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

void MailBox::addMessage(QList<Message> *list, QListWidget* listWidget ) {
    for (int i = 0; i < list->size(); ++i) {
        QWidget *message = new QWidget(window);

        QBoxLayout* layoutV = new QVBoxLayout;

        QLayout* layoutH = new QHBoxLayout;

        QLabel *sender = new QLabel(message);
        sender->setText(list->at(i).getSender());
        QLabel *theme = new QLabel(message);
        theme->setText(list->at(i).getTheme());

        layoutH->addWidget( sender );
        layoutH->addWidget( theme );

        QLayout* layoutH2 = new QHBoxLayout;

        QLabel *title = new QLabel(message);
        title->setText(list->at(i).getTitle());
        QLabel *date = new QLabel(message);
        date->setText(list->at(i).getDateTime());

        layoutH2->addWidget( title );
        layoutH2->addWidget( date );

        layoutV->addLayout(layoutH);
        layoutV->addLayout(layoutH2);

        message->setLayout( layoutV );

        QListWidgetItem* item = new QListWidgetItem( listWidget );
        item->setSizeHint( message->sizeHint() );
        listWidget ->setItemWidget( item, message);
    }

}

void MailBox::clearLayout(QLayout * layout) {
    if (! layout)
         return;
      while (auto item = layout->takeAt(0)) {
         delete item->widget();
         clearLayout(item->layout());
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
    window->setGeometry(90, 50, this->size().width()/2.5, this->size().height()-50);
}

void MailBox::onInboxClicked() {
    clearLayout(layoutVert);
    listWidget = new QListWidget;
    layoutVert->addWidget( listWidget );
    /*Сейчас пойдет заглушка для списка сообщений*/
    Message mes1("HELLO", "123", "sf", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes2("HELLO2", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes3("HELLO3", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes4("HELLO4", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes5("HELLO5", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes6("HELLO6", "123", "dgd", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    QList<Message> *list = new QList<Message>;
    list->append(mes1);
    list->append(mes2);
    list->append(mes3);
    list->append(mes4);
    list->append(mes5);
    list->append(mes6);

    addMessage(list,listWidget);
}

void MailBox::onOutboxClicked() {
    clearLayout(layoutVert);
    listWidget = new QListWidget;
    layoutVert->addWidget( listWidget );
    /*Сейчас пойдет заглушка для списка сообщений*/
    Message mes1("HELLO1", "1233", "sf", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes2("HELLO1", "1233", "dgd", "ER4", "Y4T", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    QList<Message> *list = new QList<Message>;
    list->append(mes1);
    list->append(mes2);

    addMessage(list,listWidget);
}
