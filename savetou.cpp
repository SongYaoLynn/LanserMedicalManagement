#include "savetou.h"
#include "ui_savetou.h"
#include "precisetreatment.h"

SaveToU::SaveToU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveToU)
{
    ui->setupUi(this);
    warning = new Warning;
    saveHint = new SaveHint;
    usbChoose = new USBChoose;
    connect(usbChoose, SIGNAL(usbSelectedSignal(QString)), this, SLOT(getUSBSeledted(QString)));
    connect(saveHint, SIGNAL(repetitiveNamesSignal(QStringList,bool,bool)), this, SLOT(repetitionDeal(QStringList,bool,bool)));
}

SaveToU::~SaveToU()
{
    delete ui;
}

void SaveToU::saveToUInit()
{
    showState = true;
    userInfoLocal = PreciseTreatment::userInfo;
    ui->userList->clear();
    ui->selectedList->clear();
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

void SaveToU::on_preBtn_clicked()
{
    showState = false;
    emit changeDispalySignal(0);
}

void SaveToU::on_searchBtn_clicked()
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
            saveToUInit();
        }
    }
    else{
        warning->warningShow("没有找到用户信息");
    }

}
//移动单个
void SaveToU::signalMove(QListWidget *src, QListWidget *trg)
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
//移动所有
void SaveToU::multiMove(QListWidget *src, QListWidget *trg)
{
    if(src->count()){
        //src数量 <= trg数量
        if(src->count() == 1 && !listContains(src->item(0)->text(), trg)){
            trg->addItem(src->item(0)->text());
            src->takeItem(0);
        }
        //src数量 > trg数量
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

bool SaveToU::listContains(QString srcValue, QListWidget *trg)
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
    else{
        return false;
    }
}

void SaveToU::on_toSelected_clicked()
{
    signalMove(ui->userList, ui->selectedList);
}

void SaveToU::on_toSelectedAll_clicked()
{
    multiMove(ui->userList, ui->selectedList);
}

void SaveToU::on_toUser_clicked()
{
    signalMove(ui->selectedList, ui->userList);
}

void SaveToU::on_toUserAll_clicked()
{
    multiMove(ui->selectedList, ui->userList);
}

void SaveToU::on_saveBtn_clicked()
{
    //得到当前所选用户的信息
    if(ui->selectedList->count()){
      int selectedNum;
      for(selectedNum = 0; selectedNum < ui->selectedList->count(); selectedNum++){
          QString selectedName = ui->selectedList->item(selectedNum)->text();
          selectedUser[selectedName] = userInfoLocal[selectedName];
      }
      //usb设备信息
      QMap<QString, USBDevice> usbInfoNow = usbCollectionInfo->usbDeviceMap;
      if(!usbInfoNow.isEmpty() && usbInfoNow.size()){
          usbChoose->usbChooseInit();   //选择u盘
      }
      else{
          warning->warningShow("没有检测到可用设备");
      }
    }
    else{
        warning->warningShow("没有需要保存的用户信息");
    }
}
//选择u盘后，保存所选用户信息
void SaveToU::getUSBSeledted(QString usbSelected)
{
    if(showState){
        if(!usbSelected.isEmpty()){
            filePath = usbSelected + ":/test/test.txt"; //文件地址===需改
            // 判断所选用户信息是否存在
            infoFromU = *FileOperation::readFromFile(filePath);
            QMap<QString, User>::iterator infoIt;
            if(!infoFromU.isEmpty()){
                for(infoIt = selectedUser.begin(); infoIt != selectedUser.end(); ++infoIt){
                    if(infoFromU.contains(infoIt.key())){
                        repetitiveList << infoIt.key();
                    }
                    else {
                        combinationMap[infoIt.key()] = selectedUser[infoIt.key()];
                    }
                }
                for(infoIt = infoFromU.begin(); infoIt != infoFromU.end(); ++infoIt){
                    if(!selectedUser.contains(infoIt.key())){
                        combinationMap[infoIt.key()] = infoFromU[infoIt.key()];
                    }

                }
                //有重复
                if(repetitiveList.size()){
                    saveHint->saveHintShow(repetitiveList);
                }
                //没有重复
                else{
                    if(FileOperation::writeToFile(filePath, combinationMap)){
                        warning->warningShow("保存成功");
                    }
                    else{
                        warning->warningShow("文件打开失败");
                    }
                }
            }
            //文件打开失败或文件为空
            else{
                if(FileOperation::writeToFile(filePath, selectedUser)){
                    warning->warningShow("保存成功");
                }
                else{
                    warning->warningShow("文件打开失败");
                }
            }
        }
        else{
            warning->warningShow("没有需要保存的用户信息");
        }
    }
}
//重复项处理
void SaveToU::repetitionDeal(QStringList repetitiveName, bool allState, bool replaceState)
{
    while (repetitiveName.size()) {
        if(allState){
            if(replaceState){
                for(int i = 0; i < repetitiveName.size(); i++){
                    combinationMap[repetitiveName.at(i)] = selectedUser[repetitiveName.at(i)];
                }
            }
            else{
                for(int i = 0; i < repetitiveName.size(); i++){
                    combinationMap[repetitiveName.at(i)] = infoFromU[repetitiveName.at(i)];
                }
            }
            if(FileOperation::writeToFile(filePath, combinationMap)){
                warning->warningShow("保存成功");
            }
            else{
                warning->warningShow("文件打开失败");
            }
            repetitiveName.clear();
        }
        else{
//            if(replaceState){
//                QStringList repetitiveCurent;
//                repetitiveCurent << repetitiveName.at(0);
//                QMap<QString, User> currentList = getMapFromName(repetitiveCurent);
//                if(FileOperation::writeToFile(filePath, currentList)){
////                    warning->warningShow("保存成功");
//                }
//                else{
//                    warning->warningShow("文件打开失败");
//                }
//            }
//            repetitiveName.removeFirst();
//            if(repetitiveName.size()){
//                saveHint->saveHintShow(repetitiveName); ///////
//            }
        }
    }
}
