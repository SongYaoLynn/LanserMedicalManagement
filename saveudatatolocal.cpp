#include "saveudatatolocal.h"
#include "ui_saveudatatolocal.h"
#include "precisetreatment.h"

SaveUDataToLocal::SaveUDataToLocal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveUDataToLocal)
{
    ui->setupUi(this);
    warning = new Warning;
    saveHint = new SaveHint;
}

SaveUDataToLocal::~SaveUDataToLocal()
{
    delete ui;
}

void SaveUDataToLocal::saveUToLocalInit()
{
    ui->userList->clear();
    QMap<QString, User>::iterator userIt;
    if(!userInfoLocal.empty()){
        for(userIt = userInfoLocal.begin(); userIt != userInfoLocal.end(); ++userIt){
            ui->userList->addItem(userIt.key());
        }
    }
    else{
        warning->warningShow("没有找到用户信息");
    }
}

void SaveUDataToLocal::on_preBtn_clicked()
{
    showState = false;
    emit changeDispalySignal(0);
}

void SaveUDataToLocal::signalMove(QListWidget *src, QListWidget *trg)
{
    if(!src->selectedItems().isEmpty()){
        if(!listContains(src->currentItem()->text(), trg)){
            trg->addItem(src->currentItem()->text());
            src->takeItem(src->currentRow());
        }
        else{
            warning->warningShow("当前用户已存在");
        }

    }
    else {
        warning->warningShow("请选择用户");
    }
}

void SaveUDataToLocal::multiMove(QListWidget *src, QListWidget *trg)
{
    if(src->count()){
        if(src->count() == 1 && !listContains(src->item(0)->text(), trg)){
            trg->addItem(src->item(0)->text());
            src->takeItem(0);
        }
        else if(src->count() > 1){
            if(trg->count() == 1 && listContains(trg->item(0)->text(), src)){
                trg->clear();
            }
            int itemNum;
            for(itemNum = 0; itemNum < src->count(); itemNum++){
                trg->addItem(src->item(itemNum)->text());
            }
            src->clear();
        }
        else{
            warning->warningShow("当前用户已存在");
        }
    }
    else {
        warning->warningShow("没有可选择的用户");
    }
}

bool SaveUDataToLocal::listContains(QString srcValue, QListWidget *trg)
{
    if(trg->count()){
        int itemNum;
        for(itemNum = 0; itemNum < trg->count(); itemNum++){
            if(trg->item(itemNum)->text() == srcValue){
                return true;
            }
        }
        return false;
    }
    return false;
}

void SaveUDataToLocal::on_searchBtn_clicked()
{
    if(!userInfoLocal.empty()){
        QString searchName(ui->searchName->text());
        if(!searchName.isEmpty() && searchName != " "){
            if(userInfoLocal.contains(searchName)){
                resultIt = userInfoLocal.find(searchName);
                ui->userList->clear();
                ui->userList->addItem(resultIt.key());
            }
            else {
                warning->warningShow("没有找到该用户");
            }
        }
        else {
            warning->warningShow("搜索内容不能为空！请重新输入");
            saveUToLocalInit();
        }
    }
    else{
        warning->warningShow("没有找到用户信息");
    }
}

void SaveUDataToLocal::on_toSelected_clicked()
{
    signalMove(ui->userList, ui->selectedList);
}

void SaveUDataToLocal::on_toSelectedAll_clicked()
{
    multiMove(ui->userList, ui->selectedList);
}

void SaveUDataToLocal::on_toUser_clicked()
{
    signalMove(ui->selectedList, ui->userList);
}

void SaveUDataToLocal::on_toUserAll_clicked()
{
    multiMove(ui->selectedList, ui->userList);
}

void SaveUDataToLocal::getUSBSelected(QString usbSelected)
{
    if(!usbSelected.isEmpty()){
        QString filePath = usbSelected + ":/test/test.txt"; //文件地址===需改
        userInfoLocal = *(FileOperation::readFromFile(filePath));
        if(!userInfoLocal.isEmpty()){
            showState = true;
            emit changeDispalySignal(5);
            saveUToLocalInit();
        }
        else{
            warning->warningShow("文件为空或打开失败");
        }
    }

}

void SaveUDataToLocal::on_saveBtn_clicked()
{
    //得到当前所选用户的信息
    if(ui->selectedList->count()){
      int selectedNum;
      for(selectedNum = 0; selectedNum < ui->selectedList->count(); selectedNum++){
          QString selectedName = ui->selectedList->item(selectedNum)->text();
          if(!PreciseTreatment::userInfo.contains(selectedName)){
              PreciseTreatment::userInfo[selectedName] = userInfoLocal[selectedName];
          }
          else{
              saveHint->saveHintShow(selectedName);
          }

      }
      warning->warningShow("保存成功");
      emit reloadSignal();
      emit writeToFileSignal();
    }
    else{
        warning->warningShow("没有需要保存的用户信息");
    }
}

void SaveUDataToLocal::repetitionDeal(QString repetitiveName, bool replaced)
{
    if(replaced){
        PreciseTreatment::userInfo[repetitiveName] = userInfoLocal[repetitiveName];
    }
}
