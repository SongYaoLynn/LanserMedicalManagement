#ifndef WARNING_H
#define WARNING_H

#include <QDialog>

namespace Ui {
class Warning;
}

class Warning : public QDialog
{
    Q_OBJECT

public:
    explicit Warning(QWidget *parent = 0);
    ~Warning();
    void warningShow(QString info);

private:
    Ui::Warning *ui;
};

#endif // WARNING_H
