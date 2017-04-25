#include "mailbox.h"
#include "ui_mailbox.h"

MailBox::MailBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MailBox)
{
    ui->setupUi(this);
}

MailBox::~MailBox()
{
    delete ui;
}
void MailBox::resizeEvent(QResizeEvent *event){
    this->changeSize();
}

void MailBox::changeSize()
{
    ui->logout->setGeometry(this->size().width()-75,0, 75, 31);
    ui->line->setGeometry(0, 20,this->size().width()-20, 20);
    ui->line_2->setGeometry(83, 30, 20, this->size().height-20);
}
