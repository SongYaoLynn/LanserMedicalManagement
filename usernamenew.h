#ifndef USERNAMENEW_H
#define USERNAMENEW_H

#include <QDialog>

namespace Ui {
class UserNameNew;
}

class UserNameNew : public QDialog
{
    Q_OBJECT

public:
    explicit UserNameNew(QWidget *parent = 0);
    ~UserNameNew();
signals:
    void changeDispalySignal(int);

private slots:
    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::UserNameNew *ui;
};

#endif // USERNAMENEW_H
