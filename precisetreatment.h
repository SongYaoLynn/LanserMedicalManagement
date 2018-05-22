#ifndef PRECISETREATMENT_H
#define PRECISETREATMENT_H

#include <QWidget>
#include <QStackedLayout>
#include <QVBoxLayout>
#include "usernew.h"
#include "usernamenew.h"
#include "useredit.h"
#include "savetou.h"
#include "saveudatatolocal.h"
#include "warning.h"
#include "usersavedsetting.h"
#include "hint.h"
#include "usbchoose.h"

#include "global.h"
#include "serialport.h"
#include "precisioninfo.h"
#include "usbdevice.h"
#include "usbcollection.h"
#include "fileoperation.h"

#include <qwt_dial_needle.h>
#include <QMap>
#include <QTimer>
#include <QTime>

extern SerialPort serialPort;

namespace Ui {
class PreciseTreatment;
}

class PreciseTreatment : public QWidget
{
    Q_OBJECT

public:
    explicit PreciseTreatment(QWidget *parent = 0);
    ~PreciseTreatment();
    //用户信息
    static QMap<QString, User> userInfo;   //  用户信息
signals:
    void changeDispalySignal(int);
    void areaChooseSignal(int); //  当前选择的治疗区域
    void userSavedShowSignal(QString);//  用户设置界面弹框

private slots:
    void changeDisplay(int index); // 切换页面
    void getArea(QString currentUsername, quint8 area);   //  得到当前选择的治疗区域,刷新精准治疗界面
    void hintTimerZero();   //计时结束
    void reload();  // 刷新用户
    void writeToFile(); //保存到本地

    void on_userSetComboBox_activated(int index);

    void on_clearBtn_clicked();

    void on_test_clicked();     //test-----------

    void on_stateBtn_clicked();

    void on_gears_valueChanged(double value);

    void on_gears_sliderReleased();

private:
    Ui::PreciseTreatment *ui;
    QStackedLayout *stackLayout;
    // 相关界面
    UserNew *userNew;
    UserNameNew *userNameNew;
    UserEdit *userEdit;
    SaveToU *saveToU;
    SaveUDataToLocal *saveUDataToLocal;
    UserSavedSetting *userSavedSetting;
    Warning *warning;
    Hint *hint;
    USBChoose *usbChoose;
    // 文件操作
    FileOperation fileOperation;

    bool laserDialogState = false;  //  激光出光提示框显示状态：true--显示，false--关闭
    bool userSelected = false;  //是否选择了用户
    QString nameCurrent;
    quint8 areaCurrent = 0;   //治疗区域：0--没有选择治疗区域
    quint16 numOne = 100;  //数值1==========

    void preciseTreatmentInit();    //初始化
    void refreshWords(PatientItem patientData, quint8  rings, quint16 valueOne, bool state);//初始显示-true；档位环变化-false
    QTime secondsToQTime(quint16 seconds);
    quint16 qTimeToSeconds(QTime time);
    void setState(bool state);  //设置userSelected和档位环的状态
    void renewPatientCurrent(quint8 rings, quint16 seconds);
    PatientItem getCurrentPatient();
};

#endif // PRECISETREATMENT_H
