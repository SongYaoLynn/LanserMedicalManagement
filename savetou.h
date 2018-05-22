#ifndef SAVETOU_H
#define SAVETOU_H

#include <QWidget>
#include <QListWidget>
#include "warning.h"
#include "precisioninfo.h"
#include "fileoperation.h"
#include "usbdevice.h"
#include "usbcollection.h"
#include "global.h"
#include "usbchoose.h"

namespace Ui {
class SaveToU;
}

class SaveToU : public QWidget
{
    Q_OBJECT

public:
    explicit SaveToU(QWidget *parent = 0);
    ~SaveToU();


    void saveToUInit();
signals:
    void changeDispalySignal(int);

private slots:
    void on_preBtn_clicked();

    void on_searchBtn_clicked();

    void on_toSelected_clicked();

    void on_toSelectedAll_clicked();

    void on_toUser_clicked();

    void on_toUserAll_clicked();

    void on_saveBtn_clicked();

    void getUSBSeledted(QString usbSelected);

private:
    Ui::SaveToU *ui;
    Warning *warning;
    USBChoose *usbChoose;
    QMap<QString, User> userInfoLocal;   //  本地用户信息
    QMap<QString, User>::iterator resultIt; //  搜索结果
    QMap<QString, User> selectedUser;   // 所选用户信息
    bool showState = false; // 显示：true；不显示：false
//    USBDevice usbDevice;
//    USBCollection usbCollectionNow;

    void signalMove(QListWidget *src, QListWidget *trg);    //单项移动
    void multiMove(QListWidget *src, QListWidget *trg); //全体移动
    bool listContains(QString srcValue, QListWidget *trg);  //判断trg中是否有srcValue项
    bool checkUsb(QString checkInfo);   //  检查U盘是否符合要求
};

#endif // SAVETOU_H
