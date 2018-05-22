#include "precisetreatment.h"
#include "ui_precisetreatment.h"
#include <QStackedLayout>
#include <QVBoxLayout>

QMap<QString, User> PreciseTreatment::userInfo;
//USBCollection PreciseTreatment::usbCollection;

PreciseTreatment::PreciseTreatment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreciseTreatment)
{
    ui->setupUi(this);
    // 显示指针
    QwtDialSimpleNeedle *dial_needle ;
    dial_needle = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow, true, Qt::gray, Qt::darkGray);
    ui->gears->setNeedle(dial_needle);

    userNew = new UserNew;
    userNameNew = new UserNameNew;
    userEdit = new UserEdit;
    saveToU = new SaveToU;
    saveUDataToLocal = new SaveUDataToLocal;
    userSavedSetting = new UserSavedSetting;
    warning = new Warning;
    hint = new Hint;    //激光出光时的弹出框（包含定时器）
    usbChoose = new USBChoose;

    // 初始化
    preciseTreatmentInit();

    // 页面转换
    stackLayout = new QStackedLayout;
    stackLayout->addWidget(this);
    stackLayout->addWidget(userNew);
    stackLayout->addWidget(userNameNew);
    stackLayout->addWidget(userEdit);
    stackLayout->addWidget(saveToU);
    stackLayout->addWidget(saveUDataToLocal);

    // 页面切换
    connect(this, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int)));    //精准治疗主界面 0
    connect(userNew, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //新建用户设置 1
    connect(userNameNew, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //用户名输入 2
    connect(userEdit, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //编辑 3
    connect(saveToU, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //保存到U盘 4
    connect(saveUDataToLocal, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //保存U盘数据到本地 5
    connect(this, SIGNAL(userSavedShowSignal(QString)), userSavedSetting, SLOT(userSavedSettingShow(QString)));// 已保存用户设置

    //页面初始化/刷新
    connect(userNew, SIGNAL(initSignal()), userNameNew, SLOT(usernameNewInit()));   // 用户名输入界面初始化
    connect(userNameNew, SIGNAL(reloadSignal()), this, SLOT(reload())); //用户名刷新
    connect(userEdit, SIGNAL(reloadSignal()), this, SLOT(reload())); //用户名刷新
    connect(saveUDataToLocal, SIGNAL(reloadSignal()), this, SLOT(reload())); //用户名刷新

    // 参数传递
    connect(userSavedSetting, SIGNAL(areaNew(QString, quint8)), this, SLOT(getArea(QString, quint8))); //当前所选治疗区域
    connect(hint, SIGNAL(timerZeroSignal()), this, SLOT(hintTimerZero()));  //计时器归零
    connect(userNew, SIGNAL(userNewInfoSignal(User)), userNameNew, SLOT(getUserNewInfo(User)));    // 新建-->用户名输入
    connect(userNameNew, SIGNAL(writeToFileSignal()), this, SLOT(writeToFile()));   // 刷新本地文件信息
    connect(userEdit, SIGNAL(writeToFileSignal()), this, SLOT(writeToFile()));  //刷新本地文件信息
    connect(saveUDataToLocal, SIGNAL(writeToFileSignal()), this, SLOT(writeToFile()));
    connect(usbChoose, SIGNAL(usbSelectedSignal(QString)), saveUDataToLocal, SLOT(getUSBSelected(QString))); //当前所选的u盘

}

PreciseTreatment::~PreciseTreatment()
{
    delete ui;
}

void PreciseTreatment::changeDisplay(int index)
{
    stackLayout->setCurrentIndex(index);
}

//函数功能：刷新精准治疗
//参数：当前所选用户名、所选的治疗区域
void PreciseTreatment::getArea(QString currentUsername, quint8 area)
{
    setState(true);    //已经选择了用户
    nameCurrent = currentUsername;
    areaCurrent = area;
    PatientItem patientCurrent = getCurrentPatient();
    refreshWords(patientCurrent, patientCurrent.getRings(), numOne, true);
}

// 激光出光计时结束，00：00：00
void PreciseTreatment::hintTimerZero()
{
    if(serialPort.sendAndReceiveCompare(serialPort.hexToByte(LASER_CLOSE), serialPort.hexToByte(LASER_CLOSE)) && laserDialogState){
        hint->close();
        ui->timeSurplus->setTime(hint->timeCurrrnt);
        laserDialogState = false;
    }

}
// 刷新下拉菜单中的用户名信息
void PreciseTreatment::reload()
{
    int itemNum;
    for(itemNum = ui->userSetComboBox->count()-1; itemNum > 3; itemNum--){
        ui->userSetComboBox->removeItem(itemNum);
    }
    QMap<QString, User>::iterator infoIt;
    if(!userInfo.empty()){
        for(infoIt = userInfo.begin(); infoIt != userInfo.end(); ++infoIt){
            ui->userSetComboBox->addItem(infoIt.key());
        }
    }
}
//页面切换
void PreciseTreatment::on_userSetComboBox_activated(int index)
{
    if (index < 4)
    {
        switch (index) {
        case 0:
            emit changeDispalySignal(1);
            userNew->userNewInit();
            setState(false);
            break;
        case 1:
        {
            if(!userInfo.isEmpty()){
                emit changeDispalySignal(3);
                userEdit->userEditInit();
            }
            else {
                warning->warningShow("当前没有可编辑的用户");
            }
            setState(false);
            break;
        }
        case 2:
            emit changeDispalySignal(4);
            saveToU->saveToUInit();
            setState(false);
            break;
        case 3:
            usbChoose->usbChooseInit();
            setState(false);
            break;
        default:
            break;
        }

    }
    else
    {
        emit userSavedShowSignal(ui->userSetComboBox->currentText());
    }

}
// 精准治疗界面初始化
void PreciseTreatment::preciseTreatmentInit()
{
    //    遍历用户数据，得到所有的用户名，并显示
    QMap<QString, User>::iterator infoIt;
    if(!userInfo.empty()){
        for(infoIt = userInfo.begin(); infoIt != userInfo.end(); ++infoIt){
            ui->userSetComboBox->addItem(infoIt.key());
        }
    }
    ui->userSetComboBox->setCurrentIndex(0);
    ui->text1->setText(tr("0"));
    ui->text2->setText(tr("0"));
    ui->gears->setValue(0);
    ui->timeSurplus->setTime(QTime(0,0,0));
    ui->skinColorLabel->setText(tr("III"));
    ui->stateBtn->setText(tr("待机"));
    setState(false);
}

void PreciseTreatment::refreshWords(PatientItem patientData, quint8 rings, quint16 valueOne, bool state)
{
    quint16 timeRemaining;
    quint16 wordTwo = rings * patientData.getSeconds();
    quint16 wordOne = valueOne - wordTwo;
    if(state){
        quint16 timeTotal= valueOne / rings;
        timeRemaining = timeTotal - patientData.getSeconds();
    }
    else{
        timeRemaining = valueOne / rings;
    }
    ui->text1->setText(QString::number(wordOne));
    ui->text2->setText(QString::number(wordTwo));
    ui->timeSurplus->setTime(secondsToQTime(timeRemaining));
    ui->gears->setValue(rings);
}

QTime PreciseTreatment::secondsToQTime(quint16 seconds)
{
    QTime time(0, 0, 0);
    QTime result;
    result = time.addSecs(seconds);
    return result;
}

quint16 PreciseTreatment::qTimeToSeconds(QTime time)
{
    return (time.second() + time.minute()*60 +time.hour()*3600);
}

void PreciseTreatment::setState(bool state)
{
    userSelected = state;
    ui->gears->setEnabled(state);
}

void PreciseTreatment::renewPatientCurrent(quint8 rings, quint16 seconds)
{
    PatientItem patientNew = getCurrentPatient();
    patientNew.setRings(rings);
    patientNew.setSeconds(seconds);
    switch (areaCurrent) {
    case 1:
        userInfo[nameCurrent].setPatientItem(patientNew, userInfo[nameCurrent].getItem2(),userInfo[nameCurrent].getItem3());
        break;
    case 2:
        userInfo[nameCurrent].setPatientItem(userInfo[nameCurrent].getItem1(), patientNew,userInfo[nameCurrent].getItem3());
        break;
    case 3:
        userInfo[nameCurrent].setPatientItem(userInfo[nameCurrent].getItem1(), userInfo[nameCurrent].getItem2(),patientNew);
        break;
    default:
        break;
    }
}

PatientItem PreciseTreatment::getCurrentPatient()
{
    switch (areaCurrent) {
    case 1:
        return userInfo[nameCurrent].getItem1();
        break;
    case 2:
        return userInfo[nameCurrent].getItem2();
        break;
    case 3:
        return userInfo[nameCurrent].getItem3();
        break;
    default:
        break;
    }
}


void PreciseTreatment::on_clearBtn_clicked()
{
    ui->text2->setText(tr("0"));
}
// test按钮
void PreciseTreatment::on_test_clicked()
{
    hint = new Hint;
    QTime timeOld = ui->timeSurplus->time();
    hint->hintShow(timeOld);
    //    if(!hint->timerState){
    //        hint->close();
    //    }

}

// 准备/待机按键
void PreciseTreatment::on_stateBtn_clicked()
{
    bool state = false; //true--准备状态；false--待机状态
    QByteArray standBy = serialPort.hexToByte(STANDBY);
    QByteArray preparation = serialPort.hexToByte(PREPARATION);
    QByteArray receivedData;

    if(serialPort.sendAndReceiveCompare(standBy, standBy)){
        ui->stateBtn->setText("准备");
        state = true;
        while(state){
            receivedData = serialPort.receiveData;
//            switch (receivedData) {
//            case serialPort.hexToByte(FIBER_INSERT):
//                warning->warningShow("请插入光纤");  // 插入光纤
//                break;
//            case serialPort.hexToByte(LASER_SHOT).toLongLong():  // 激光出光
//            {
//                QTime timeOld = ui->timeSurplus->time();
//                if ((timeOld.second() || timeOld.minute() || timeOld.hour())) {
//                    hint->hintShow(timeOld);
//                    laserDialogState = true;
//                }
//                break;
//            }
//            case serialPort.hexToByte(LASER_OFF).toLongLong():   //  激光关光
//            {
//                hint->timer->stop();
//                ui->timeSurplus->setTime(hint->timeCurrrnt);
//                hint->close();
//                laserDialogState = false;
//                break;
//            }
//            case serialPort.hexToByte(DRIVE_976_ERROR).toLongLong():
//                warning->warningShow("error2:设备故障，请联系厂家维修");
//                break;
//            case serialPort.hexToByte(DRIVE_808_ERROR).toLongLong():
//                warning->warningShow("error3:设备故障，请联系厂家维修");
//                break;
//            default:
//                break;
//            }
            // 插入光纤
            if(receivedData == serialPort.hexToByte(FIBER_INSERT)){
                warning->warningShow("请插入光纤");
            }
            // 激光出光
            else if (receivedData == serialPort.hexToByte(LASER_SHOT)) {
                QTime timeOld = ui->timeSurplus->time();
                if ((timeOld.second() || timeOld.minute() || timeOld.hour())) {
                    hint->hintShow(timeOld);
                    laserDialogState = true;
                }
            }
            //  激光关光
            else if (receivedData == serialPort.hexToByte(LASER_OFF) && laserDialogState) {
                hint->timer->stop();
                ui->timeSurplus->setTime(hint->timeCurrrnt);
                hint->close();
                laserDialogState = false;
            }
            // error2
            else if (receivedData == serialPort.hexToByte(DRIVE_976_ERROR)) {
                warning->warningShow("error2:设备故障，请联系厂家维修");
            }
            // error3
            else if (receivedData == serialPort.hexToByte(DRIVE_808_ERROR)) {
                warning->warningShow("error3:设备故障，请联系厂家维修");
            }
            // 转到“待机”状态
            if(serialPort.sendAndReceiveCompare(preparation, preparation)){
                ui->stateBtn->setText("待机");
                state = false;
            }
        }
    }
}

void PreciseTreatment::writeToFile()
{
    //=======路径需改==========================
    QString filePath = "E:/Code/LaserMedicalManagement/test/file/1.txt";
    if(!fileOperation.writeToFile(filePath, userInfo)){
        warning->warningShow("打开文件错误");
    }
}

// 档位环操作==============有bug
void PreciseTreatment::on_gears_valueChanged(double value)
{
//    bool correct = false;
//    if(userSelected){
//        quint16 gearValueOld = patientCurrent.getRings();  //  原来的档位
//        QByteArray test8 = "test8"; //  根据档位信息得到的指令=====需改
//        if (serialPort.sendAndReceiveCompare(test8, test8)){
//            refreshWords(patientCurrent, value, numOne, false);
//            quint8 ringsNew = value;
//            quint16 secondsNew = qTimeToSeconds(ui->timeSurplus->time());
//            renewPatientCurrent(ringsNew, secondsNew);
//            correct = true;
//            qDebug("返回正确");
//            //  高亮显示0~value
//            //==============================
//        }
//        else if(!correct) {
//            qDebug("返回错误");
//            ui->gears->setValue(gearValueOld);
//        }

//    }

}

void PreciseTreatment::on_gears_sliderReleased()
{
    quint8 value = ui->gears->value();
    if(userSelected){
        quint16 gearValueOld;  //  原来的档位
        gearValueOld = getCurrentPatient().getRings();
        QByteArray test8 = "test8"; //  根据档位信息得到的指令=====需改
        if (serialPort.sendAndReceiveCompare(test8, test8)){
            refreshWords(getCurrentPatient(), value, numOne, false);
            quint8 ringsNew = value;
            quint16 secondsNew = qTimeToSeconds(ui->timeSurplus->time());
            renewPatientCurrent(ringsNew, secondsNew);
            qDebug("返回正确");
            //  高亮显示0~value
            //==============================
        }
        else {
            qDebug("返回错误");
            ui->gears->setValue(gearValueOld);
        }

    }
}
