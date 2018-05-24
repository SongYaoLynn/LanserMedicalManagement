#ifndef USEREDIT_H
#define USEREDIT_H

#include <QWidget>
#include <precisioninfo.h>
#include "warning.h"
#include <QLabel>
#include <QSpinBox>

namespace Ui {
class UserEdit;
}

class UserEdit : public QWidget
{
    Q_OBJECT

public:
    explicit UserEdit(QWidget *parent = 0);
    ~UserEdit();

    void userEditInit();

signals:
    void changeDispalySignal(int);
    void reloadSignal();
    void writeToFileSignal();
private slots:
    void on_preBtn_clicked();

    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

    void on_item1_3_1_valueChanged(int arg1);

    void on_item2_3_1_valueChanged(int arg1);

    void on_item3_3_1_valueChanged(int arg1);

    void on_usernames_activated(const QString &arg1);

private:
    Ui::UserEdit *ui;
    Warning *warning;

    void showData(QString username);
    void timeChange(QLabel* label, QSpinBox* spinBoxS, int data);  //增减时间
    quint16 toSeconds(QLabel* label, QSpinBox* spinBoxS);   //将时间转为“秒”
    void toMinuteSecond(QLabel* label, QSpinBox* spinBoxS, quint16 seconds);
};

#endif // USEREDIT_H
