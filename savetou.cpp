#include "savetou.h"
#include "ui_savetou.h"

SaveToU::SaveToU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveToU)
{
    ui->setupUi(this);
}

SaveToU::~SaveToU()
{
    delete ui;
}

void SaveToU::on_preBtn_clicked()
{
    emit changeDispalySignal(0);
}
