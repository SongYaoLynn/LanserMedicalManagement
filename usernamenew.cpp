#include "usernamenew.h"
#include "ui_usernamenew.h"
#include "precisetreatment.h"

UserNameNew::UserNameNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserNameNew)
{
    ui->setupUi(this);
    warning = new Warning;
}

UserNameNew::~UserNameNew()
{
    delete ui;
}

void UserNameNew::usernameNewInit()
{
    ui->userNameEdit->clear();
}

void UserNameNew::getUserNewInfo(User userNewInfo)
{
    usernameInfo = userNewInfo;
}

void UserNameNew::on_cancelBtn_clicked()
{
    emit changeDispalySignal(1);
}

void UserNameNew::on_saveBtn_clicked()
{
    QString username = ui->userNameEdit->text();
    if(!username.isEmpty() && username != " "){
        if(!PreciseTreatment::userInfo.contains(username)){
            usernameInfo.setUserName(username);
            PreciseTreatment::userInfo[username] = usernameInfo;
            emit changeDispalySignal(0);
            emit reloadSignal();
            emit writeToFileSignal();
        }
        else {
            warning->warningShow("用户名已存在，请重新输入");
        }
    }
    else {
        warning->warningShow("用户名不能为空");
    }

}
