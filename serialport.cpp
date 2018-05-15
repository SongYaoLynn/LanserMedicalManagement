#include "serialport.h"
#include <QDebug>


SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    receiveData = "";
    serial = NULL;
    mcount = 0;
    findAvailablePort();
    initializePort();
}

SerialPort::~SerialPort()
{
    if(serial)
    {
        delete serial;
        serial = NULL;
    }
}


void SerialPort::findAvailablePort()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort availablePort;
        availablePort.setPort(info);
        if(availablePort.open(QIODevice::ReadWrite))    //串口是否可用
        {
            if(mcount < MAX_PORT_COUNT)
            {
                portName[mcount] = availablePort.portName();
                availablePort.close();
                mcount ++;
            }
        }
    }
}

void SerialPort::initializePort()
{
    serial = new QSerialPort;

    serial->setPortName("COM3");

    serial->open(QIODevice::ReadWrite);

    serial->setBaudRate(BAUDRATE);       //设置波特率


    switch(BITNUM)//设置数据位数
    {
    case 8:
        serial->setDataBits(QSerialPort::Data8);
        break;
    default:
        break;
    }

    switch(PARITYBIT)   //设置奇偶校验
    {
    case 0:
        serial->setParity(QSerialPort::NoParity);
        break;
    default:
        break;
    }

    switch(STOPBIT)     //设置停止位
    {
    case 1:
        serial->setStopBits(QSerialPort::OneStop);
        break;
    case 2:
        serial->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        break;
    }

    serial->setFlowControl(QSerialPort::NoFlowControl);    //设置流控制

    QObject::connect(serial, &QSerialPort::readyRead, this, &SerialPort::readData);  //连接信号槽
}

void SerialPort::sendData(const QByteArray data)
{
    serial->write(data);
    serial->flush();
}

void SerialPort::readData()
{
    receiveData.clear();                           //清空原有数据
    receiveData = serial->readAll();
}

QByteArray SerialPort::hexToByte(qint64 i)
{
    QByteArray abyte;
    abyte.resize(5);
    abyte[4] = (uchar)  (0x00000000ff & i);
    abyte[3] = (uchar) ((0x000000ff00 & i) >> 8);
    abyte[2] = (uchar) ((0x0000ff0000 & i) >> 16);
    abyte[1] = (uchar) ((0x00ff000000 & i) >> 24);
    abyte[0] = (uchar) ((0xff00000000 & i) >> 32);
    return abyte;
}

bool SerialPort::sendAndReceiveCompare(const QByteArray data, const QByteArray targetData)
{
    receiveData.clear();                            //清空接收数据
    bool state = false;                             //发送和接收数据操作结果

    for(int i = 0; i < TRY_TIMES; i++)
    {
        sendData(data);                             //发送数据

        for(int j = 0; j < TRY_TIMES; j++)
        {
            delayMSecSuspend(DELAY_MS);             //给一定延时
            if(receiveData == targetData)           //如果发送数据和接收数据相等
            {
                state = true;
                break;
            }
        }
        if(state)
            break;

    }
    return state;
}

QByteArray SerialPort::sendAndReceive(const QByteArray data)
{
    receiveData.clear();                            //清空接收数据
    for(int i = 0; i < TRY_TIMES; i++)
    {
        sendData(data);                             //发送数据

        for(int j = 0; j < TRY_TIMES; j++)
        {
            delayMSecSuspend(DELAY_MS);             //给一定延时
            if(receiveData.size() != 0)             //已经接收到了数据
                break;
        }
        if(receiveData.size() != 0)
            break;

    }
    return receiveData;
}


void SerialPort::delayMSecSuspend(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void SerialPort::closePort()
{
    serial->clear();
    serial->close();
    serial->deleteLater();
}
