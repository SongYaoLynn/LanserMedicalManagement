#ifndef USERSAVEDSETTING_H
#define USERSAVEDSETTING_H

#include <QDialog>
#include "warning.h"

namespace Ui {
class UserSavedSetting;
}

class UserSavedSetting : public QDialog
{
    Q_OBJECT

public:
    explicit UserSavedSetting(QWidget *parent = 0);
    ~UserSavedSetting();
    quint8 area = 0;   //当前治疗区域
    QString currentUserneme = "";
signals:
    void areaChooseSignal(quint8);
    void areaNew(QString, quint8);
private slots:
    void on_areaBtn1_clicked();

    void on_areaBtn2_clicked();

    void on_areaBtn3_clicked();

    void on_cancelBtn_clicked();
private slots:
    void areaChoose(quint8 area);
    void on_submitBtn_clicked();
    void userSavedSettingShow(QString title);
private:
    Ui::UserSavedSetting *ui;
    Warning *warning;

};

#endif // USERSAVEDSETTING_H
