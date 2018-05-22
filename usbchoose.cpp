#include "usbchoose.h"
#include "ui_usbchoose.h"

USBChoose::USBChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::USBChoose)
{
    ui->setupUi(this);
    warning = new Warning;
//    Qt::WindowFlags flags = Qt::Dialog;
//    flags = Qt::CustomizeWindowHint;    //Qt::SubWindow 窗口没有按钮但是有标题栏
////                                        Qt::SplashScreen 标题栏也没有 按钮也没
////                                         有在那里出现就站在那里不到，也不能移动和拖到，
////                                         任务栏右击什么也没有，任务栏窗口名也没有，可以任务栏关闭
//    this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal);  //  禁止主窗口的操作
}

USBChoose::~USBChoose()
{
    delete ui;
}

void USBChoose::usbChooseInit()
{
    ui->usbList->clear();
    QMap<QString, USBDevice> usbInfoNow = usbCollectionInfo->usbDeviceMap;
    QMap<QString, USBDevice>::iterator usbIt;
    if(!usbInfoNow.isEmpty()){
        // usb检查=========
        for(usbIt = usbInfoNow.begin(); usbIt != usbInfoNow.end(); ++usbIt){
            ui->usbList->addItem(usbIt.key());
        }
    }
    this->show();
}

void USBChoose::on_cancelBtn_clicked()
{
    this->close();
}

void USBChoose::on_submitBtn_clicked()
{
    if(!ui->usbList->selectedItems().isEmpty()){
        emit usbSelectedSignal(ui->usbList->currentItem()->text());
        this->close();
    }
    else{
        warning->warningShow("请选择U盘");
    }
}
