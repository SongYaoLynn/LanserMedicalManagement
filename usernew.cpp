#include "usernew.h"
#include "ui_usernew.h"

UserNew::UserNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserNew)
{
    ui->setupUi(this);
}

UserNew::~UserNew()
{
    delete ui;
}

void UserNew::on_saveBtn_clicked()
{
    emit changeDispalySignal(2);
}

void UserNew::on_cancelBtn_clicked()
{
    emit changeDispalySignal(0);
}
