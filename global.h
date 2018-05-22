#ifndef GLOBAL_H
#define GLOBAL_H
#include "serialport.h"
#include "usbcollection.h"


extern SerialPort serialPort;             //全局串口资源类
extern USBCollection *usbCollectionInfo;              //usb设备信息
//串口控制指令宏定义

#define EQUIPMENT_NORMAL 0xff02ffeeee     //设备正常指示
#define EQUIPMENT_ERROR  0xffb0b0b0ee     //设备故障error1
#define TEMPERATURE_LOW  0xffb3b3b3ee     //设备温度较低
#define TEMPERATURE_HIG  0xffb4b4b4ee     //设备温度较高，5分钟计时，还是收到该指令error2
#define SKIN_5_6         0xffa4a4a4ee     //5、6等级肤色设定
#define SKIN_1_4         0xffa3a3a3ee     //1、2、3、4等级肤色设定
#define DRIVE_CURRENT    0xaf××××××××     //激光器驱动电流设置
#define STANDBY          0xffa9a9a9ee     //待机指令
#define PREPARATION      0xffaaaaaaee     //准备指令
#define FIBER_INSERT     0xffc2c2c2ee     //提示插入光纤
#define FIBER_READY      0xFFc3c3c3ee     //光纤设备插入，上位机不相应
#define LASER_SHOT       0xffb9b9b9ee     //激光器出光
#define LASER_OFF        0xffc0c0c0ee     //激光器关光
#define LASER_CLOSE      0xffaeaeaeee     //激光器关闭
#define DRIVE_976_NORMAL 0xffb7b7b7ee     //976驱动正常
#define DRIVE_976_ERROR  0xffb5b5b5ee     //976驱动故障
#define DRIVE_808_NORMAL 0xffb8b8b8ee     //808驱动正常
#define DRIVE_808_ERROR  0xffb6b6b6ee     //808驱动故障

#define HAND_CA  0xffa6a6a6ee     //手动：长按触发控制指令
#define HAND_CF  0xffa5a5a5ee     //手动：点击时触发控制指令
#define FOOT_CA  0xffa8a8a8ee     //脚动：长按触发控制指令
#define FOOT_CF  0xFfa7a7a7ee     //脚动：点击时触发控制指令


#endif // GLOBAL_H
