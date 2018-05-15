#include "instruction.h"
#include "ui_instruction.h"

Instruction::Instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Instruction)
{
    ui->setupUi(this);
}

Instruction::~Instruction()
{
    delete ui;
}

void Instruction::on_instructionBtn1_clicked()
{
//    QString local_path = QString(QDir::currentPath());

////    QString local_path1 = (QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
////    QStringList local_path2 = (QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation));
////    ui->instructionBtn1->setText(local_path2[0]);

//    QString path = QString("file:///") + local_path;
//    QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));


}
