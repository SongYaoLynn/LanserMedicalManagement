#include "precisetreatment.h"
#include "instruction.h"
#include "parametersetting.h"
#include "global.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PreciseTreatment w;
    usbCollectionInfo = new USBCollection();  //  usb设备信息

//    Instruction w;
//    ParameterSetting w;
    w.show();

    return a.exec();
}
