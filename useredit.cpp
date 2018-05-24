#include "useredit.h"
#include "ui_useredit.h"
#include "precisetreatment.h"

UserEdit::UserEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserEdit)
{
    ui->setupUi(this);
    warning = new Warning;
}

UserEdit::~UserEdit()
{
    delete ui;
}

void UserEdit::timeChange(QLabel *label, QSpinBox *spinBoxS, int data)
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
// 分：秒-->秒
quint16 UserEdit::toSeconds(QLabel *label, QSpinBox *spinBoxS)
{
    quint16 minute = label->text().toUInt();
    quint16 second = spinBoxS->value();
    return (minute * 60 + second);
}
// 秒-->分：秒
void UserEdit::toMinuteSecond(QLabel *label, QSpinBox *spinBoxS, quint16 seconds)
{
    label->setText(QString::number(seconds / 60));
    spinBoxS->setValue(seconds % 60);
}
//初始化/重载刷新
void UserEdit::userEditInit()
{
    ui->usernames->clear();
    QMap<QString, User> userEditInfo = PreciseTreatment::userInfo;
    QMap<QString, User>::iterator infoIt;
    if(!userEditInfo.isEmpty()){
        for(infoIt = userEditInfo.begin(); infoIt != userEditInfo.end(); ++infoIt){
            ui->usernames->addItem(infoIt.key());
        }
        showData(ui->usernames->currentText());
    }

}

//上一页
void UserEdit::on_preBtn_clicked()
{
    emit changeDispalySignal(0);
    emit reloadSignal();
}

// 保存
void UserEdit::on_saveBtn_clicked()
{
    User userInfoNew;
    PatientItem item1, item2, item3;
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

    userInfoNew.setPatientItem(item1, item2, item3);
    PreciseTreatment::userInfo[ui->usernames->currentText()] = userInfoNew;
//    userEditInit();
    warning->warningShow("保存成功");
    emit reloadSignal();
    emit writeToFileSignal();
}
// 删除按键
void UserEdit::on_cancelBtn_clicked()
{
    QMap<QString, User>::iterator infoIt;
    if(PreciseTreatment::userInfo.contains(ui->usernames->currentText())){
        for(infoIt = PreciseTreatment::userInfo.begin(); infoIt != PreciseTreatment::userInfo.end(); ){
            if(infoIt.key() == ui->usernames->currentText()){
                PreciseTreatment::userInfo.erase(infoIt++);
                emit writeToFileSignal();
                emit reloadSignal();
                break;
            }
            else {
                infoIt++;
            }
        }
    }
    else {
        warning->warningShow("要删除对象不存在");

    }
    if(!PreciseTreatment::userInfo.isEmpty()){
        userEditInit();
    }
    else {
        emit changeDispalySignal(0);
        emit writeToFileSignal();
        emit reloadSignal();
    }
}
// 根据所选用户名显示数据
void UserEdit::showData(QString username)
{
    User userSelected = PreciseTreatment::userInfo[username];
    PatientItem item1 = userSelected.getItem1();
    PatientItem item2 = userSelected.getItem2();
    PatientItem item3 = userSelected.getItem3();

    ui->areaEdit1->setText(item1.getRegion());
    ui->areaEdit2->setText(item2.getRegion());
    ui->areaEdit3->setText(item3.getRegion());

    ui->item1_1->setValue(item1.getRings());
    ui->item2_1->setValue(item2.getRings());
    ui->item3_1->setValue(item3.getRings());

    ui->item1_2->setValue(item1.getPulse());
    ui->item2_2->setValue(item2.getPulse());
    ui->item3_2->setValue(item3.getPulse());

    toMinuteSecond(ui->item1_3_2, ui->item1_3_1, item1.getSeconds());
    toMinuteSecond(ui->item2_3_2, ui->item2_3_1, item2.getSeconds());
    toMinuteSecond(ui->item3_3_2, ui->item3_3_1, item3.getSeconds());
}

void UserEdit::on_item1_3_1_valueChanged(int arg1)
{
    timeChange(ui->item1_3_2, ui->item1_3_1, arg1);
}

void UserEdit::on_item2_3_1_valueChanged(int arg1)
{
    timeChange(ui->item2_3_2, ui->item2_3_1, arg1);
}

void UserEdit::on_item3_3_1_valueChanged(int arg1)
{
    timeChange(ui->item3_3_2, ui->item3_3_1, arg1);
}

void UserEdit::on_usernames_activated(const QString &arg1)
{
    showData(arg1);
}
