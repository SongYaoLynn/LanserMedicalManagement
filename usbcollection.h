#ifndef USBCOLLECTION_H
#define USBCOLLECTION_H

#include <QMainWindow>
#include <windows.h>
#include <QMap>
#include <dbt.h>
#include <QTimer>
#include <QPalette>
#include <QString>
#include <QDebug>

#include "usbdevice.h"

class USBCollection : public QMainWindow
{
    Q_OBJECT
public:
    explicit USBCollection(QWidget *parent = nullptr);
    ~USBCollection();
    void registerDevice();                             //USB设备的注册
    QMap<QString, USBDevice> usbDeviceMap;             //用来存储U盘信息的Map
private:
    char FirstDriveFromMask (ULONG unitmask);
//    QMap<QString, USBDevice> usbDeviceMap;             //用来存储U盘信息的Map
    QStringList m_usbList;                             //存储U盘中间信息

protected:
    bool nativeEvent(const QByteArray & eventType, void * message, long*result);

signals:

public slots:
};

#endif // USBCOLLECTION_H
