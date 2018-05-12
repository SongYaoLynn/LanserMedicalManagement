#include "warning.h"
#include "ui_warring.h"

Warring::Warring(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Warring)
{
    ui->setupUi(this);
}

Warring::~Warring()
{
    delete ui;
}
