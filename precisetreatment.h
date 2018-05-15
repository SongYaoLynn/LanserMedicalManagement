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
#include "precisioninfo.h"
#include "usersavedsetting.h"
#include <qwt_dial_needle.h>
#include <QMap>
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
    User *user;
    QMap<QString, User> userInfo;
    quint8 areaTreatment = 0;   //治疗区域：0--没有选择治疗区域

signals:
    void changeDispalySignal(int);
    void areaChooseSignal(int); //  当前选择的治疗区域
    void userSavedShowSignal(QString);//  用户设置界面弹框
private slots:

    void changeDisplay(int index); // 切换页面
    quint8 getArea(quint8 area);   //  得到当前选择的治疗区域

    void on_userSetComboBox_activated(int index);

    void on_clearBtn_clicked();

    void on_test_clicked();     //test-----------

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

    void preciseTreatmentInit(User *user);    //初始化
    void reloadPreciseTreatment(QString username, quint8 area); //根据所选用户名和治疗区域更新精准治疗界面的显示

};

#endif // PRECISETREATMENT_H
