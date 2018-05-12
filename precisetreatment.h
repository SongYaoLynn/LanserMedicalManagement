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
#include "testdata.h" //测试数据
#include "warning.h"
namespace Ui {
class PreciseTreatment;
}

class PreciseTreatment : public QWidget
{
    Q_OBJECT

public:
    explicit PreciseTreatment(QWidget *parent = 0);
    ~PreciseTreatment();

    int area = 0; //治疗区域
    void userSavedSetting(QString username);

signals:
    void changeDispalySignal(int);
    void areaChooseSignal(int); //  当前选择的治疗区域

private slots:

    void changeDisplay(int index); // 切换页面

    void on_userSetComboBox_activated(int index);
    void areaGetOne();  //获取当前所选治疗区域
    void areaGetTwo();
    void areaGetThree();
    void areaSubmit();  //治疗区域选择--确认
    void areaCancel();  //治疗区域选择--取消
    void areaChoose(int area);  //治疗区域选择


    void on_clearBtn_clicked();

    void on_test_clicked();     //test-----------

private:
    Ui::PreciseTreatment *ui;
    QStackedLayout *stackLayout;
    QVBoxLayout *vBoxLayout;
    QDialog *dlg;
    QPushButton *areaBtn1;
    QPushButton *areaBtn2;
    QPushButton *areaBtn3;
    QPushButton *submitBtn;
    QPushButton *cancelBtn;

    UserNew *userNew;
    UserNameNew *userNameNew;
    UserEdit *userEdit;
    SaveToU *saveToU;
    SaveUDataToLocal *saveUDataToLocal;
    Warning *warning;

    void preciseTreatmentInit();    //初始化

};

#endif // PRECISETREATMENT_H
