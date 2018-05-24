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
#include "savehint.h"

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

    void repetitionDeal(QStringList repetitiveName, bool allState, bool replaceState);//对重复项的处理

private:
    Ui::SaveToU *ui;
    Warning *warning;
    SaveHint *saveHint;
    USBChoose *usbChoose;
    QMap<QString, User> userInfoLocal;   //  本地用户信息
    QMap<QString, User>::iterator resultIt; //  搜索结果
    QMap<QString, User> selectedUser;   // 所选用户信息
    bool showState = false; // 显示：true；不显示：false
    QString filePath;   //文件地址
    QStringList repetitiveList; //重复项用户名集
    QMap<QString, User> infoFromU;  // u盘中的用户信息
    QMap<QString, User> combinationMap; //整合的用户信息

    void signalMove(QListWidget *src, QListWidget *trg);    //单项移动
    void multiMove(QListWidget *src, QListWidget *trg); //全体移动
    bool listContains(QString srcValue, QListWidget *trg);  //判断trg中是否有srcValue项
};

#endif // SAVETOU_H
