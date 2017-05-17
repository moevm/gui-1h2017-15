#include "loginwindow.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;
    w.show();
//    MailBox m;
//    m.show();

    return a.exec();
}
