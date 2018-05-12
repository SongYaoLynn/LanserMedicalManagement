#include "useredit.h"
#include "ui_useredit.h"

UserEdit::UserEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserEdit)
{
    ui->setupUi(this);
}

UserEdit::~UserEdit()
{
    delete ui;
}

void UserEdit::on_preBtn_clicked()
{
    emit changeDispalySignal(0);
}
