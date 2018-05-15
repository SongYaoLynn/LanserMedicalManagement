#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include "precisioninfo.h"

class FileOperation
{
public:
    static quint8 writeToFile(QString path, QMap<QString, User> &);     //把用户集合写入文件
    static QMap<QString, User>* readFromFile(QString path);             //从文件中读取用户集合
};

#endif // FILEOPERATION_H
