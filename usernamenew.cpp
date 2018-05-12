#include "usernamenew.h"
#include "ui_usernamenew.h"

UserNameNew::UserNameNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserNameNew)
{
    ui->setupUi(this);
}

UserNameNew::~UserNameNew()
{
    delete ui;
}

void UserNameNew::on_cancelBtn_clicked()
{
    emit changeDispalySignal(1);
}

void UserNameNew::on_saveBtn_clicked()
{
    emit changeDispalySignal(0);
}
