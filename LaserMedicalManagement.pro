#-------------------------------------------------
#
# Project created by QtCreator 2018-05-12T11:32:12
#
#-------------------------------------------------

QT       += core gui

QT       += serialport

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
    warning.cpp \
    usersavedsetting.cpp \
    precisioninfo.cpp \
    guidanceinfo.cpp \
    saveudatatolocal.cpp \
    fileoperation.cpp \
    global.cpp \
    serialport.cpp \
    usbcollection.cpp \
    usbdevice.cpp \
    hint.cpp \
    usbchoose.cpp \
    savehint.cpp

HEADERS += \
        precisetreatment.h \
    usernew.h \
    usernamenew.h \
    useredit.h \
    savetou.h \
    saveudatatolocal.h \
    warning.h \
    precisioninfo.h \
    usersavedsetting.h \
    guidanceinfo.h \
    fileoperation.h \
    global.h \
    serialport.h \
    usbcollection.h \
    usbdevice.h \
    hint.h \
    usbchoose.h \
    savehint.h

FORMS += \
        precisetreatment.ui \
    usernew.ui \
    usernamenew.ui \
    useredit.ui \
    savetou.ui \
    saveudatatolocal.ui \
    warning.ui \
    usersavedsetting.ui \
    hint.ui \
    usbchoose.ui \
    savehint.ui

RESOURCES += \
    images.qrc \
    pdf.qrc

# qwt
DEFINES += QT_DLL QWT_DLL
LIBS += -L"D:\Qt\Qt5.10.1\5.10.1\mingw53_32\lib" -lqwtd
LIBS += -L"D:\Qt\Qt5.10.1\5.10.1\mingw53_32\lib" -lqwt
INCLUDEPATH += D:\Qt\Qt5.10.1\5.10.1\mingw53_32\include\qwt


