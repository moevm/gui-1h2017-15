#include "sendmessage.h"
#include "ui_sendmessage.h"

SendMessage::SendMessage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendMessage)
{
    ui->setupUi(this);
    connect( ui->sendMessage, SIGNAL( clicked() ), SLOT( onSendClicked() ) );
}

SendMessage::SendMessage(QString name) :
    QMainWindow(0),
    ui(new Ui::SendMessage)
{
    ui->setupUi(this);
    connect( ui->sendMessage, SIGNAL( clicked() ), SLOT( onSendClicked() ) );
    this->sender=name;
}

SendMessage::~SendMessage()
{
    delete ui;
}

void SendMessage::resizeEvent(QResizeEvent *event){
    this->changeSize();
}

void SendMessage::changeSize()
{
    ui->lineEdit->setGeometry(60,20, this->size().width()-80, 20);
    ui->lineEdit_2->setGeometry(60, 60,this->size().width()-80, 20);
    ui->textEdit->setGeometry(10, 90, this->size().width()-30, this->size().height()-160);
    ui->sendMessage->setGeometry(10, this->size().height() - 60, this->size().width()-30, 35);
}

void SendMessage::onSendClicked() {
    Message(ui->lineEdit_2->text(), ui->lineEdit_2->text(), ui->textEdit->toPlainText(), this->sender, ui->lineEdit->text(), QDateTime::currentDateTime());
}
