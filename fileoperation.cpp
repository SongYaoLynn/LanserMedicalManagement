#include "fileoperation.h"

//函数功能：把要固化的数据写入文件
//函数参数：路径、QMap类型的用户集合
//返回值：0-打开文件错误  1-写数据成功
quint8 FileOperation::writeToFile(QString path, QMap<QString, User> & userCollection)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open File Fail!" ;
        return 0;
    }
    QDataStream ds(&file);
    ds << userCollection ;
    file.close();
    return 1;
}

//函数功能：从指定文件读取用户集合
//函数参数：路径
//返回值：NULL 读取失败 否则返回用户集合指针
QMap<QString, User>* FileOperation::readFromFile(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open File Fail!" ;
        return NULL;
    }

    QDataStream ds(&file);
    QMap<QString, User>  userData;
    ds >> userData;
    QMap<QString, User>* userCollection = new QMap<QString, User>(userData);

    return userCollection;
}
