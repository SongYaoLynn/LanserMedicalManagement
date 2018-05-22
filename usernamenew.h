#ifndef USERNAMENEW_H
#define USERNAMENEW_H

#include <QDialog>
#include <precisioninfo.h>
#include "warning.h"

namespace Ui {
class UserNameNew;
}

class UserNameNew : public QDialog
{
    Q_OBJECT

public:
    explicit UserNameNew(QWidget *parent = 0);
    ~UserNameNew();
    User usernameInfo;

signals:
    void changeDispalySignal(int);
    void reloadSignal();
    void writeToFileSignal();

private slots:
    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

    void getUserNewInfo(User userNewInfo);  //得到新建用户页面信息
    void usernameNewInit(); //用户输入界面初始化

private:
    Ui::UserNameNew *ui;
    Warning *warning;
};

#endif // USERNAMENEW_H
