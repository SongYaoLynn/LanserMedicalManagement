#include "saveudatatolocal.h"
#include "ui_saveudatatolocal.h"

SaveUDataToLocal::SaveUDataToLocal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveUDataToLocal)
{
    ui->setupUi(this);
}

SaveUDataToLocal::~SaveUDataToLocal()
{
    delete ui;
}

void SaveUDataToLocal::on_preBtn_clicked()
{
    emit changeDispalySignal(0);
}
