#include "precisetreatment.h"
#include "global.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PreciseTreatment w;
    usbCollectionInfo = new USBCollection();  //  usb设备信息
    w.show();

    return a.exec();
}
