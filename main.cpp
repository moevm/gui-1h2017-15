#include "loginwindow.h"
#include "connectionManager.h"
#include <QMessageBox>
#include <QApplication>
#include <smtp.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;
    w.show();  

    return a.exec();
}
