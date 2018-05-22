#include "usersavedsetting.h"
#include "ui_usersavedsetting.h"

UserSavedSetting::UserSavedSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSavedSetting)
{
    ui->setupUi(this);
    warning = new Warning;
    connect(this, SIGNAL(areaChooseSignal(quint8)), this, SLOT(areaChoose(quint8)));
}

UserSavedSetting::~UserSavedSetting()
{
    delete ui;
}

void UserSavedSetting::userSavedSettingShow(QString title)
{
    currentUserneme = title;
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
}

void UserSavedSetting::on_submitBtn_clicked()
{
    if(!area){        
        warning->warningShow("请选择区域");
    }
    else {
        emit areaNew(currentUserneme, area);
        this->close();
    }

}
