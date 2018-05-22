#include "savehint.h"
#include "ui_savehint.h"

SaveHint::SaveHint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveHint)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags = Qt::CustomizeWindowHint;    //Qt::SubWindow 窗口没有按钮但是有标题栏
//                                        Qt::SplashScreen 标题栏也没有 按钮也没
//                                         有在那里出现就站在那里不到，也不能移动和拖到，
//                                         任务栏右击什么也没有，任务栏窗口名也没有，可以任务栏关闭
    this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal);  //  禁止主窗口的操作
}

SaveHint::~SaveHint()
{
    delete ui;
}

void SaveHint::saveHintShow(QString repetitiveName)
{
    ui->name->setText(repetitiveName);
    this->repetitiveName = repetitiveName;
    this->show();
}

void SaveHint::on_submitBtn_clicked()
{
    emit saveHintSignal(repetitiveName, true);
    this->close();
}

void SaveHint::on_cancelBtn_clicked()
{
    emit saveHintSignal(repetitiveName, false);
    this->close();
}
