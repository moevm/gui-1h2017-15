#include "sendmessage.h"
#include "ui_sendmessage.h"
#include "smtpconnectionmanager.h"
#include <QMessageBox>

SendMessage::SendMessage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendMessage)
{
    ui->setupUi(this);

    SmtpConnectionManager *instance = SmtpConnectionManager::getInstance();
    instance->addConnectionListener(this);

    connect( ui->sendMessage, SIGNAL( clicked() ), SLOT( onSendClicked() ) );
}

SendMessage::SendMessage(QString name) :
    QMainWindow(0),
    ui(new Ui::SendMessage)
{
    SmtpConnectionManager *instance = SmtpConnectionManager::getInstance();
    instance->addConnectionListener(this);

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

void SendMessage::connected(bool success, QString message)
{

}

void SendMessage::loggedIn(bool success, QString message)
{

}

void SendMessage::messageSent(bool success, QString message)
{
    QMessageBox messageBox;
    if (success) {
        messageBox.setText("Message has been sent!");
    } else {
        messageBox.setText("Message hasn't been sent! ");
    }

    messageBox.exec();

    SmtpConnectionManager *instance = SmtpConnectionManager::getInstance();
    instance->removeConnectionListener(this);

    this->close();
}

void SendMessage::changeSize()
{
    ui->lineEdit->setGeometry(60,20, this->size().width()-80, 20);
    ui->lineEdit_2->setGeometry(60, 60,this->size().width()-80, 20);
    ui->textEdit->setGeometry(10, 90, this->size().width()-30, this->size().height()-160);
    ui->sendMessage->setGeometry(10, this->size().height() - 60, this->size().width()-30, 35);
}

void SendMessage::onSendClicked() {
    Message message(ui->lineEdit_2->text(), ui->lineEdit_2->text(), ui->textEdit->toPlainText(), this->sender, ui->lineEdit->text(), QDateTime::currentDateTime());
    SmtpConnectionManager *instance = SmtpConnectionManager::getInstance();
    instance->sendMessage(message);
}
