#include "usersavedsetting.h"
#include "ui_usersavedsetting.h"

UserSavedSetting::UserSavedSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSavedSetting)
{
    ui->setupUi(this);

    connect(this, SIGNAL(areaChooseSignal(quint8)), this, SLOT(areaChoose(quint8)));
}

UserSavedSetting::~UserSavedSetting()
{
    delete ui;
}

void UserSavedSetting::userSavedSettingShow(QString title)
{
    this->setWindowTitle(title);
    this->show();
}

void UserSavedSetting::on_areaBtn1_clicked()
{
    emit areaChooseSignal(1);
}

void UserSavedSetting::on_areaBtn2_clicked()
{
    emit areaChooseSignal(2);
}

void UserSavedSetting::on_areaBtn3_clicked()
{
    emit areaChooseSignal(3);
}

void UserSavedSetting::on_cancelBtn_clicked()
{
    this->close();
}

void UserSavedSetting::areaChoose(quint8 area)
{
    if(area > 0){
        this->area = area;
    }
    else {
        this->area = 0;
    }
    qDebug("当前选择%d\n", area);
}

void UserSavedSetting::on_submitBtn_clicked()
{
    if(!area){
        warning = new Warning;
        warning->warningShow(tr("请选择治疗区域！"));
    }
    else {
        qDebug("保存%d\n", area);
        emit areaNew(area);
        this->close();
    }

}
