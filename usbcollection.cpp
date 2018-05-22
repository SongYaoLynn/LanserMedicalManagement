#include "usbcollection.h"
USBCollection::USBCollection(QWidget *parent) : QMainWindow(parent)
{
    registerDevice();
}

USBCollection::~USBCollection()
{

}

char USBCollection::FirstDriveFromMask(ULONG unitmask)
{
    char i;
    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1)
            break;
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}

bool USBCollection::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType==WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:

            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags ==0)
                {
                    QString USBDisk = QString(this->FirstDriveFromMask(lpdbv ->dbcv_unitmask));
                    qDebug() << "USB_Arrived and The USBDisk is: "<<USBDisk ;
                    USBDevice usbDevice;
                    //此时的U盘信息存储在m_usbList
                    if (m_usbList.count() >= 6) {

                        usbDevice.setInformation(USBDisk, m_usbList.at(0), m_usbList.at(1), m_usbList.at(4),
                                                 m_usbList.at(5), m_usbList.at(2), m_usbList.at(3));
                    }
                    else if(m_usbList.count() >= 3)
                    {
                        usbDevice.setInformation(USBDisk, m_usbList.at(0), m_usbList.at(1), "",
                                                 "", m_usbList.at(2), "");

                    }
                    usbDeviceMap.insert(USBDisk, usbDevice);
                    qDebug() << "USB_ADD MapSIZE : " << usbDeviceMap.size();

                }
            }
            if(lpdb->dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE)
            {
                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;
                QString strname = QString::fromWCharArray(pDevInf->dbcc_name);
                //对U盘信息进行提取
                if (!strname.isEmpty() && strname.length() > 10 ) {
                    if (strname.contains("USBSTOR")) {
                        QStringList listAll = strname.split('#');
                        QStringList listInfo = listAll.at(1).split('&');
                        m_usbList.append(listInfo.at(1).mid(4));    //设备制造商 3
                        m_usbList.append(listInfo.at(2).mid(5));    //设备型号 4
                        m_usbList.append(listInfo.at(3).mid(4));    //设备版本 5
                    }else {
                        m_usbList.clear();
                        QStringList listAll = strname.split('#');
                        QStringList listID = listAll.at(1).split('&');
                        m_usbList.append(listID.at(0).right(4));    //vid 0
                        m_usbList.append(listID.at(1).right(4));    //pid 1
                        m_usbList.append(listAll.at(2));            //设备序列号 2
                    }
                }
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags == 0)
                {
                    QString USBDisk = QString(this->FirstDriveFromMask(lpdbv ->dbcv_unitmask));
                    qDebug() << "USB_Removed is : " << USBDisk;
                    if(usbDeviceMap.contains(USBDisk))
                        usbDeviceMap.remove(USBDisk);
                    qDebug() << "USB_Remov MapSIZE : " << usbDeviceMap.size();
                }
            }
            break;
        }
    }
    return false;
}

void USBCollection::registerDevice()
{
    const GUID GUID_DEVINTERFACE_LIST[] = {
        { 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
        { 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } }};

    HDEVNOTIFY hDevNotify;
    DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
    ZeroMemory(&NotifacationFiler,sizeof(DEV_BROADCAST_DEVICEINTERFACE));
    NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

    for(int i=0;i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID);i++)
    {
        NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];

        hDevNotify = RegisterDeviceNotification((HANDLE)this->winId(),&NotifacationFiler,DEVICE_NOTIFY_WINDOW_HANDLE);
        if(!hDevNotify)
        {
            qDebug() << QStringLiteral("register error!") <<endl;
        }
    }
}
