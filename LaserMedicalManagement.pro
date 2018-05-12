#-------------------------------------------------
#
# Project created by QtCreator 2018-05-12T11:32:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaserMedicalManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        precisetreatment.cpp \
    usernew.cpp \
    usernamenew.cpp \
    useredit.cpp \
    savetou.cpp \
    saveudatatolocal.cpp \
    warning.cpp \
    instruction.cpp

HEADERS += \
        precisetreatment.h \
    usernew.h \
    usernamenew.h \
    useredit.h \
    savetou.h \
    saveudatatolocal.h \
    testdata.h \
    warning.h \
    instruction.h

FORMS += \
        precisetreatment.ui \
    usernew.ui \
    usernamenew.ui \
    useredit.ui \
    savetou.ui \
    saveudatatolocal.ui \
    warning.ui \
    instruction.ui

RESOURCES += \
    images.qrc
