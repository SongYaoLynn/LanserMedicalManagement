#ifndef USERNEW_H
#define USERNEW_H

#include <QDialog>

namespace Ui {
class UserNew;
}

class UserNew : public QDialog
{
    Q_OBJECT

public:
    explicit UserNew(QWidget *parent = 0);
    ~UserNew();
signals:
    void changeDispalySignal(int);

private slots:
    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::UserNew *ui;
};

#endif // USERNEW_H
