#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QTime>
#include <QCoreApplication>

#define MAX_PORT_COUNT 10    //定义最大串口数量
#define BAUDRATE 9600        //串口波特率
#define BITNUM 8             //数据位
#define STOPBIT 1            //停止位
#define PARITYBIT 0          //奇偶校验位

#define TRY_TIMES 3          //数据发送并接收最大尝试次数
#define DELAY_MS 5000         //发送数据后等待的时间


//串口资源类
class SerialPort : public QObject
{
    Q_OBJECT
public:
  explicit SerialPort(QObject *parent = nullptr);
  ~SerialPort();
  void findAvailablePort();                       //查找有效串口
  void initializePort();                          //初始化串口（打开串口）
  void sendData(const QByteArray data);           //发送数据
  void readData();                                //接收数据
  void closePort();                               //关闭串口
  bool sendAndReceiveCompare(const QByteArray data, const QByteArray targetData);
                                                  //发送并接收数据,入参：发送数据、要匹配的数据
  QByteArray sendAndReceive(const QByteArray data);
                                                  //发送并接收收据，返回接收结果
  QByteArray hexToByte(qint64 i);                 //把16进制数据转化为字节

  QByteArray receiveData;                       //存储串口接收到的数据

private:
//    QByteArray receiveData;                       //存储串口接收到的数据
    QSerialPort *serial;                          //串口
    int mcount;                                   //可用串口的数量
    QString portName[MAX_PORT_COUNT];             //可用串口名称
    void delayMSecSuspend(unsigned int msec);     //阻塞延时
signals:

public slots:

};

#endif // SERIALPORT_H
