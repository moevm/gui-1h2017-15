#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "smtpconnectionmanager.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    Address gmailAddress("smtp.mail.ru", 465);
    connectionManager = SmtpConnectionManager::createInstance(this, gmailAddress);

    mailBox = new MailBox();
    connect(mailBox, &MailBox::firstWindow, this, &LoginWindow::resetConnection);
   // testMsg();
}

void LoginWindow::logIn()
{
}

void LoginWindow::connected(bool success, QString message)
{
    qDebug() << "connected to the server or not " << message << endl;
}

void LoginWindow::testMsg()
{
    Pop3Client client(true, true, true);

    bool a1 = client.Connect("pop.mail.ru", 995);
    bool a2 = client.Login(ui->uname->text(), ui->password->text());

    QVector<Pop3Client::MessageId> vector;

    bool succ = client.GetMsgList(vector);

    for (int i = 6; i < vector.size(); i++)
    {
        QString message;
        client.GetMessage(vector.at(i).first, message);
        Message mss;
        MyParser a;
        mss = a.parseMail(message);
        qDebug() << message;
    }

}

void LoginWindow::loggedIn(bool success, QString message)
{
    QMessageBox messageBox;
    if (success) {
        //messageBox.setText("Signed in successfully");
        Pop3Client client(true, true, true);

         bool success = client.Connect("pop.mail.ru", 995);
         bool another = client.Login(ui->uname->text(), ui->password->text());

         QVector<Pop3Client::MessageId> vector;

         bool succ = client.GetMsgList(vector);

         QList<Message> *list = new QList<Message>;
         int i = vector.size()-1;
         int k = 0;
         while (k < 50 && vector.size() > k) { //отображение только последних 50 писем, иначе работает миллион лет
             QString message;
             client.GetMessage(vector.at(i).first, message);
             Message mss;
             MyParser a;
             mss = a.parseMail(message);
             list->append(mss);
             //qDebug() << mss.getSender();
             i--;
             k++;
         }
         mailBox->setList(list);
         mailBox->initWidget();
         mailBox->show();
         this->close();
    } else {
        messageBox.setText("Log in failed : ");
        messageBox.exec();
    }
}

void LoginWindow::messageSent(bool success, QString message)
{
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::mailSent(QString status)
{

}

void LoginWindow::clearForm()
{
    this->show();
    ui->uname->clear();
    ui->password->clear();
//    delete connectionManager;
//    Address gmailAddress("smtp.mail.ru", 465);
    //    connectionManager = SmtpConnectionManager::getInstance(this, gmailAddress);
}

void LoginWindow::resetConnection()
{
    this->connectionManager = SmtpConnectionManager::getInstance();

    clearForm();
}

void LoginWindow::on_logInButton_clicked()
{
    connectionManager->signIn(ui->uname->text(), ui->password->text());
    mailBox->setName(ui->uname->text() + ui->comboBox->currentText());
}


