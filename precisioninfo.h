#ifndef PRECISIONINFO_H
#define PRECISIONINFO_H

#include <QString>
#include <QDataStream>

//精确治疗流程数据存储

//PatientItem：存储用户一条数据
class PatientItem {
public:
    PatientItem();
    PatientItem(QString region, quint8 rings, bool pulse,  quint16 seconds);
    ~PatientItem();

    void setRegion(QString region);
    void setRings(quint8 rings);
    void setPulse(bool pulse);
    void setSeconds(quint16 seconds);

    QString getRegion();
    quint8  getRings();
    bool    getPulse();
    quint16 getSeconds();

public:
    friend QDataStream &operator<<(QDataStream & , const PatientItem &);
    friend QDataStream &operator>>(QDataStream & , PatientItem &);
                                               //重载运算符，对象的序列化和反序列化

private:
    QString region;                            //区域
    quint8  rings;                             //数值环数值1~15，调整间距0.5
    bool    pulse;                             //脉冲连续
    quint16 seconds;                           //时间，调整间隔15S
};

//User：患者用户
class User
{
public:
    User();
    ~User();

    void setPatientItem(PatientItem item1, PatientItem item2, PatientItem item3);
    void setUserName(QString userName);
    //3个item一起设置，因为其编辑在同一个页面上，而用户名在单独的页面

    QString getUserName();
    PatientItem getItem1();
    PatientItem getItem2();
    PatientItem getItem3();

public:
    friend QDataStream &operator<<(QDataStream & , const User &);
    friend QDataStream &operator>>(QDataStream & , User &);
                                               //User对象的序列化和反序列化

private:
    QString  userName;                         //用户名称
    PatientItem item1;                         //数据记录1
    PatientItem item2;                         //数据记录2
    PatientItem item3;                         //数据记录3

};

#endif // PRECISIONINFO_H
