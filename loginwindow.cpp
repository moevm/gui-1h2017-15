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
    connectionManager = SmtpConnectionManager::getInstance(this, gmailAddress);

    mailBox = new MailBox();
    connect(mailBox, &MailBox::firstWindow, this, &LoginWindow::clearForm);
}

void LoginWindow::logIn()
{
}

void LoginWindow::connected(bool success, QString message)
{
    qDebug() << "connected to the server or not " << message << endl;
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

         QString message;

         bool fff = client.GetMessage(vector.at(5).first, message);

         qDebug() << message;

         mailBox->show();
         this->close();
    } else {
        messageBox.setText("Log in failed : ");
        messageBox.exec();
    }
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

void LoginWindow::on_logInButton_clicked()
{
    connectionManager->signIn(ui->uname->text(), ui->password->text());
}
