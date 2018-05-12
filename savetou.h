#ifndef SAVETOU_H
#define SAVETOU_H

#include <QWidget>

namespace Ui {
class SaveToU;
}

class SaveToU : public QWidget
{
    Q_OBJECT

public:
    explicit SaveToU(QWidget *parent = 0);
    ~SaveToU();
signals:
    void changeDispalySignal(int);
private slots:
    void on_preBtn_clicked();

private:
    Ui::SaveToU *ui;
};

#endif // SAVETOU_H
