#ifndef SAVEUDATATOLOCAL_H
#define SAVEUDATATOLOCAL_H

#include <QWidget>
#include <QListWidget>
#include "warning.h"
#include "precisioninfo.h"
#include "fileoperation.h"
#include "usbdevice.h"
#include "usbcollection.h"
#include "savehint.h"

namespace Ui {
class SaveUDataToLocal;
}

class SaveUDataToLocal : public QWidget
{
    Q_OBJECT

public:
    explicit SaveUDataToLocal(QWidget *parent = 0);
    ~SaveUDataToLocal();

    void saveUToLocalInit();
    bool showState = false;
    QMap<QString, User> userInfoLocal;   //  读取到的用户信息
signals:
    void changeDispalySignal(int);
    void reloadSignal();
    void writeToFileSignal();
private slots:
    void on_preBtn_clicked();

    void on_searchBtn_clicked();

    void on_toSelected_clicked();

    void on_toSelectedAll_clicked();

    void on_toUser_clicked();

    void on_toUserAll_clicked();

    void getUSBSelected(QString usbSelected);

    void on_saveBtn_clicked();

    void repetitionDeal(QString repetitiveName, bool replaced);

private:
    Ui::SaveUDataToLocal *ui;
    Warning *warning;
    SaveHint *saveHint;

    QMap<QString, User>::iterator resultIt; //  搜索结果

    void signalMove(QListWidget *src, QListWidget *trg);    //单项移动
    void multiMove(QListWidget *src, QListWidget *trg); //全体移动
    bool listContains(QString srcValue, QListWidget *trg);  //判断trg中是否有srcValue项
};

#endif // SAVEUDATATOLOCAL_H
