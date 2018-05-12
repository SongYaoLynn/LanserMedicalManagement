#ifndef SAVEUDATATOLOCAL_H
#define SAVEUDATATOLOCAL_H

#include <QWidget>

namespace Ui {
class SaveUDataToLocal;
}

class SaveUDataToLocal : public QWidget
{
    Q_OBJECT

public:
    explicit SaveUDataToLocal(QWidget *parent = 0);
    ~SaveUDataToLocal();
signals:
    void changeDispalySignal(int);
private slots:
    void on_preBtn_clicked();

private:
    Ui::SaveUDataToLocal *ui;
};

#endif // SAVEUDATATOLOCAL_H
