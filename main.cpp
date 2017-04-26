#include "loginwindow.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;
    //MailBox w;
    w.show();

    return a.exec();
}
