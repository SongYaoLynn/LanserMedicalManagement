#ifndef HINT_H
#define HINT_H

#include <QDialog>
#include <QTime>
#include <QTimer>

namespace Ui {
class Hint;
}

class Hint : public QDialog
{
    Q_OBJECT

public:
    explicit Hint(QWidget *parent = 0);
    ~Hint();
    void hintShow(QTime timeOld);
    void hintClose();
    QTime timeCurrrnt;
    QTimer* timer;
signals:
    void timerZeroSignal();
private slots:
    void countdown();   //倒计时


private:
    Ui::Hint *ui;
};

#endif // HINT_H
