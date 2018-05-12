#include "warning.h"
#include "ui_warning.h"

Warning::Warning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Warning)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags); //去除弹出框右上角的问号
}

Warning::~Warning()
{
    delete ui;
}

void Warning::warningShow(QString info)
{
    ui->label->setText(info);
    this->show();
}
