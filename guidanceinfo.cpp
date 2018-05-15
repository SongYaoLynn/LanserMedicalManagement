#include "guidanceinfo.h"
#include <QString>

GuidanceInfo::GuidanceInfo()
{

}

GuidanceInfo::~GuidanceInfo()
{

}

void GuidanceInfo::setAge(quint16 age)
{
    this->age = age;
}

void GuidanceInfo::setSex(QString sex)
{
    this->sex = sex;
}

void GuidanceInfo::setHeight(quint16 height)
{
    this->height = height;
}

void GuidanceInfo::setWeight(float weight)
{
    this->weight = weight;
}

void GuidanceInfo::setSkinColor(quint8 skinColor)
{
    this->skinColor = skinColor;
}

void GuidanceInfo::setFigure(quint16 figure)
{
    this->figure = figure;
}

void GuidanceInfo::setRegion(quint8 region)
{
    this->region = region;
}

void GuidanceInfo::setSymptom(quint16 symptom)
{
    this->symptom = symptom;
}

void GuidanceInfo::setPulse(bool pulse)
{
    this->pulse = pulse;
}

quint16 GuidanceInfo::getAge()
{
    return age;
}

QString GuidanceInfo::getSex()
{
    return sex;
}

quint16 GuidanceInfo::getHeight()
{
    return height;
}

float GuidanceInfo::getWeight()
{
    return weight;
}

quint8  GuidanceInfo::getSkinColor()
{
    return skinColor;
}

quint16 GuidanceInfo::getFigure()
{
    return figure;
}

quint8  GuidanceInfo::getRegion()
{
    return region;
}

quint16 GuidanceInfo::getSymptom()
{
    return symptom;
}

bool    GuidanceInfo::getPulse()
{
    return pulse;
}
