#include "precisioninfo.h"

/*PatientItem对外函数接口*/

PatientItem::PatientItem()
{

}

PatientItem::PatientItem(QString region, quint8 rings, bool pulse, quint16 seconds)
{
    this->region = region;
    this->rings = rings;
    this->pulse = pulse;
    this->seconds = seconds;
}

PatientItem::~PatientItem()
{

}

void PatientItem::setRegion(QString region)
{
    this->region = region;
}

void PatientItem::setRings(quint8 rings)
{
    this->rings = rings;
}

void PatientItem::setPulse(bool pulse)
{
    this->pulse = pulse;
}

void PatientItem::setSeconds(quint16 seconds)
{
    this->seconds = seconds;
}

QString PatientItem::getRegion()
{
    return region;
}

quint8  PatientItem::getRings()
{
    return rings;
}

bool    PatientItem::getPulse()
{
    return pulse;
}

quint16 PatientItem::getSeconds()
{
    return seconds;
}

QDataStream & operator<<(QDataStream & output, const PatientItem &obj)
{
    output << obj.region << obj.rings << obj.pulse << obj.seconds;
    return output ;
}

QDataStream & operator>>(QDataStream & input, PatientItem & obj)
{
    input >> obj.region >> obj.rings >> obj.pulse >> obj.seconds;
    return input;
}

/*User对外接口*/
User::User() {}
User::~User() {}

void User::setPatientItem(PatientItem item1, PatientItem item2, PatientItem item3)
{
    this->item1 = item1;
    this->item2 = item2;
    this->item3 = item3;

}

void User::setUserName(QString userName)
{
    this->userName = userName;
}

QString User::getUserName()
{
   return userName;
}

PatientItem User::getItem1()
{
    return item1;
}

PatientItem User::getItem2()
{
    return item2;
}

PatientItem User::getItem3()
{
    return item3;
}

QDataStream & operator<<(QDataStream & output, const User &obj)
{
    output << obj.userName << obj.item1 << obj.item2 << obj.item3;
    return output ;
}

QDataStream & operator>>(QDataStream & input, User &obj)
{
    input >> obj.userName >> obj.item1 >> obj.item2 >> obj.item3;
    return input;
}
