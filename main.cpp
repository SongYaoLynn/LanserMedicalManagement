#include "precisetreatment.h"
#include "instruction.h"
#include "parametersetting.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PreciseTreatment w;
//    Instruction w;
//    ParameterSetting w;
    w.show();

    return a.exec();
}
