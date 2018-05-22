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
    item1.setRegion(ui->areaEdit1->text());
    item1.setRings(ui->item1_1->value());
    item1.setPulse(ui->item1_2->value());
    item1.setSeconds(toSeconds(ui->item1_3_2, ui->item1_3_1));

    item2.setRegion(ui->areaEdit2->text());
    item2.setRings(ui->item2_1->value());
    item2.setPulse(ui->item2_2->value());
    item2.setSeconds(toSeconds(ui->item2_3_2, ui->item2_3_1));

    item3.setRegion(ui->areaEdit3->text());
    item3.setRings(ui->item3_1->value());
    item3.setPulse(ui->item3_2->value());
    item3.setSeconds(toSeconds(ui->item3_3_2, ui->item3_3_1));

    userNewInfo.setPatientItem(item1, item2, item3);

    emit userNewInfoSignal(userNewInfo);
    emit changeDispalySignal(2);
    emit initSignal();
}

void UserNew::on_cancelBtn_clicked()
{
    emit changeDispalySignal(0);
}
// 初始化新建用户界面
void UserNew::userNewInit()
{
    // 区域名称
    ui->areaEdit1->setText("第一区域");
    ui->areaEdit2->setText("第二区域");
    ui->areaEdit3->setText("第三区域");
    // 数值环数值
    ui->item1_1->setValue(0);
    ui->item2_1->setValue(0);
    ui->item3_1->setValue(0);
    // 脉冲速率
    ui->item1_2->setValue(0);
    ui->item2_2->setValue(0);
    ui->item3_2->setValue(0);
    // 时间
    ui->item1_3_1->setValue(0);
    ui->item1_3_2->setText("0");
    ui->item2_3_1->setValue(0);
    ui->item2_3_2->setText("0");
    ui->item3_3_1->setValue(0);
    ui->item3_3_2->setText("0");
}

// 新建设置页面中，时间增减按键组
// 输入：显示“分钟”的QLabel，显示“秒”的QSpinBox，当前QSpinBox中的值（即“秒”）
void UserNew::timeChange(QLabel *label, QSpinBox *spinBoxS, int data)
{
    int minuteOld = label->text().toInt();
    if(data >= 60){
        spinBoxS->setValue(0);
        label->setText(QString::number(minuteOld + 1));
    }
    else if (data < 0) {
        if(minuteOld > 0){
            spinBoxS->setValue(45);
            label->setText(QString::number(minuteOld - 1));
        }
        else if (minuteOld == 0) {
            spinBoxS->setValue(0);
            label->setText("0");
        }
    }
}

quint16 UserNew::toSeconds(QLabel *label, QSpinBox *spinBoxS)
{
    quint16 minute = label->text().toUInt();
    quint16 second = spinBoxS->value();
    return (minute * 60 + second);
}

void UserNew::on_item1_3_1_valueChanged(int arg1)
{
    timeChange(ui->item1_3_2, ui->item1_3_1, arg1);
}

void UserNew::on_item2_3_1_valueChanged(int arg1)
{
    timeChange(ui->item2_3_2, ui->item2_3_1, arg1);
}

void UserNew::on_item3_3_1_valueChanged(int arg1)
{
    timeChange(ui->item3_3_2, ui->item3_3_1, arg1);
}
