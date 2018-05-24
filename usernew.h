#ifndef USERNEW_H
#define USERNEW_H

#include <QDialog>
#include <precisioninfo.h>
#include <QLabel>
#include <QSpinBox>

namespace Ui {
class UserNew;
}

class UserNew : public QDialog
{
    Q_OBJECT

public:
    explicit UserNew(QWidget *parent = 0);
    ~UserNew();
    void userNewInit(); //  新建用户界面初始化


signals:
    void changeDispalySignal(int);
    void userNewInfoSignal(User);
    void initSignal();

private slots:
    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

    void on_item1_3_1_valueChanged(int arg1);

    void on_item2_3_1_valueChanged(int arg1);

    void on_item3_3_1_valueChanged(int arg1);

private:
    Ui::UserNew *ui;

    User userNewInfo;
    PatientItem item1, item2, item3;

    void timeChange(QLabel* label, QSpinBox* spinBoxS, int data);  //增减时间
    quint16 toSeconds(QLabel* label, QSpinBox* spinBoxS);   //将时间转为“秒”

};

#endif // USERNEW_H
