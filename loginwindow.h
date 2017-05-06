#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

#include <connectionlistener.h>
#include <abstractconnectionmanager.h>
#include <smtpconnectionmanager.h>
#include <mailbox.h>
#include <Pop3Client.h>
#include <myparser.h>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow, public ConnectionListener
{
    Q_OBJECT

    SmtpConnectionManager *connectionManager;

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void mailSent(QString);
    void logIn();


    void on_logInButton_clicked();

private:
    Ui::LoginWindow *ui;
    MailBox *mailBox;

    // ConnectionListener interface
public:
    void testMsg();
    void connected(bool success, QString message);
    void loggedIn(bool success, QString message);
    void clearForm();
    void resetConnection();

};

#endif // LOGINWINDOW_H
