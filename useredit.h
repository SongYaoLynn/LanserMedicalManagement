#ifndef USEREDIT_H
#define USEREDIT_H

#include <QWidget>

namespace Ui {
class UserEdit;
}

class UserEdit : public QWidget
{
    Q_OBJECT

public:
    explicit UserEdit(QWidget *parent = 0);
    ~UserEdit();
signals:
    void changeDispalySignal(int);
private slots:
    void on_preBtn_clicked();

private:
    Ui::UserEdit *ui;
};

#endif // USEREDIT_H
