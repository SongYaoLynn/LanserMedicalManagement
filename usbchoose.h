#ifndef USBCHOOSE_H
#define USBCHOOSE_H

#include <QDialog>
#include "global.h"
#include "usbdevice.h"
#include "usbcollection.h"
#include "warning.h"

namespace Ui {
class USBChoose;
}

class USBChoose : public QDialog
{
    Q_OBJECT

public:
    explicit USBChoose(QWidget *parent = 0);
    ~USBChoose();
    void usbChooseInit();
signals:
    void usbSelectedSignal(QString);
    void changeDispalySignal(int);
private slots:
    void on_cancelBtn_clicked();


    void on_submitBtn_clicked();

private:
    Ui::USBChoose *ui;
    Warning *warning;


};

#endif // USBCHOOSE_H
