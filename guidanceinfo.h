#ifndef GUIDANCEINFO_H
#define GUIDANCEINFO_H

#include <QString>

/*治疗导向过程信息存储*/
class GuidanceInfo
{
public:
    GuidanceInfo();
    ~GuidanceInfo();

    void setAge(quint16 age);
    void setSex(QString sex);
    void setHeight(quint16 height);
    void setWeight(float weight);
    void setSkinColor(quint8 skinColor);
    void setFigure(quint16 figure);
    void setRegion(quint8 region);
    void setSymptom(quint16 symptom);
    void setPulse(bool pulse);

    quint16 getAge();
    QString getSex();
    quint16 getHeight();
    float   getWeight();
    quint8  getSkinColor();
    quint16 getFigure();
    quint8  getRegion();
    quint16 getSymptom();
    bool    getPulse();

private:
    quint16 age;
    QString sex;
    quint16 height;
    float weight;
    quint8 skinColor;                   //肤色1~6对应6种肤色
    quint16 figure;                      //体型
    quint8 region;                      //治疗区域
    quint16 symptom;                    //症状11表示序号1的症状1，121表示1.2症状的第一类，依次类推
    bool pulse;                         //脉冲是否连续

};
#endif // GUIDANCEINFO_H
