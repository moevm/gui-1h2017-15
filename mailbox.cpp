#include "mailbox.h"
#include "ui_mailbox.h"

MailBox::MailBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MailBox)
{
    ui->setupUi(this);
    connect( ui->inbox, SIGNAL( clicked() ), SLOT( onInboxClicked() ) );
    connect( ui->outbox, SIGNAL( clicked() ), SLOT( onOutboxClicked() ) );
    connect( ui->logout, SIGNAL( clicked() ), SLOT( onLogOutClicked() ) );
    connect( ui->writeMessage, SIGNAL( clicked() ), SLOT( onWriteMessageClicked() ) );
    window = new QScrollArea(this);
    window->setGeometry(90, 50, 300, 500);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::lightGray);
    window->setAutoFillBackground(true);
    window->setPalette(Pal);
    Pal.setColor(QPalette::Background, Qt::lightGray);
    ui->messageWidget ->setGeometry(590, 30, 500, 500);
    ui->messageWidget ->setAutoFillBackground(true);
    ui->messageWidget ->setPalette(Pal);
    ui->inbox->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 128, 128);"));
    ui->outbox->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 178, 170);"));
    setIcons();
    setMinimumSize(800, 600);
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
    ui->writeMessage->setGeometry(this->size().width()-185,0, 100, 31);
    ui->name->setGeometry(this->size().width()-290,0, 100, 40);
    ui->line->setGeometry(0, 20,this->size().width()-20, 20);
    ui->line_2->setGeometry(83, 30, 20, this->size().height());
    window->setGeometry(90, 50, this->size().width()/2.5, this->size().height()-50);
    ui->messageWidget->setGeometry(this->size().width()/2.5 + 100, 30 , this->size().width()/1.5, this->size().height());
    ui->date->setGeometry(this->size().width()/5 + 80 , 10 , this->size().width()/5, 20);
    ui->theme->setGeometry(70, 10 , this->size().width()/5, 20);
    ui->sender->setGeometry(100, 40 , this->size().width()/4, 20);
    ui->receirver->setGeometry(100, 70 , this->size().width()/4, 20);
    ui->textBrowser->setGeometry(10, 110 , this->size().width()/2 - 50 , ui->messageWidget->size().height() - 250);
}

void MailBox::onInboxClicked() {
    clearLayout(layoutVert);
    ui->inbox->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 128, 128);"));
    ui->outbox->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 178, 170);"));
    listWidget = new QListWidget;
    layoutVert->addWidget( listWidget );
    addMessage(listRec, listWidget);
    connectList();
}

void MailBox::onOutboxClicked() {
    clearLayout(layoutVert);
    ui->inbox->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 178, 170);"));
    ui->outbox->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 128, 128);"));
    listWidget = new QListWidget;
    layoutVert->addWidget( listWidget );
    Message mes1("HELLO1", "1233", "sf", "ER", "YT", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    Message mes2("HELLO1", "1233", "dgd", "ER4", "Y4T", QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
    QList<Message> *list = new QList<Message>;
    list->append(mes1);
    list->append(mes2);
    addMessage(list, listWidget);
    //connectList();
}

void MailBox::onLogOutClicked() {
    this->close();
    emit firstWindow();
}

void MailBox::onWriteMessageClicked() {
    SendMessage *sendMessage = new SendMessage(this->name);
    sendMessage->show();
}

void MailBox::setName(QString name) {
    this->name = name;
    ui->name->setText(name);
}

void MailBox::setList(QList<Message> *list) {
    this->listRec = list;
}

void MailBox::initWidget() {
    listWidget = new QListWidget;
    layoutVert = new QVBoxLayout;
    layoutVert->addWidget( listWidget );
    window->setLayout( layoutVert );
    addMessage(listRec,listWidget);
    connectList();
}

void MailBox::on_listWidget_clicked(QListWidgetItem *item)
{
    int row = listWidget->row(item);
    ui->sender->setText(listRec->at(row).getSender());
    ui->receirver->setText(listRec->at(row).getReceiver());
    ui->date->setText(listRec->at(row).getDateTime());
    ui->theme->setText(listRec->at(row).getTheme());
    //вывод текста
    ui->textBrowser->setText(listRec->at(row).getBodyHTML().getMessage());
}

void MailBox::connectList()
{
    connect( listWidget, SIGNAL( itemClicked(QListWidgetItem *) ),this,  SLOT( on_listWidget_clicked(QListWidgetItem *) ));
    emit on_listWidget_clicked(listWidget->item(0));
}
