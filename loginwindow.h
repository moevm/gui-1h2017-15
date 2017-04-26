#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

#include <connectionlistener.h>
#include <abstractconnectionmanager.h>
#include <smtpconnectionmanager.h>
#include <pop3client.h>

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

    // ConnectionListener interface
public:
    void connected(bool success, QString message);
    void loggedIn(bool success, QString message);

};

#endif // LOGINWINDOW_H
