#include "hint.h"
#include "ui_hint.h"

Hint::Hint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hint)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags = Qt::CustomizeWindowHint;    //Qt::SubWindow 窗口没有按钮但是有标题栏
//                                        Qt::SplashScreen 标题栏也没有 按钮也没
//                                         有在那里出现就站在那里不到，也不能移动和拖到，
//                                         任务栏右击什么也没有，任务栏窗口名也没有，可以任务栏关闭
    this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal);  //  禁止主窗口的操作
}

Hint::~Hint()
{
    delete ui;
}


void Hint::countdown()
{
    QTime timeOld = ui->timeSurplus->time();
    QTime timeNew;
    if((timeCurrrnt.second() || timeCurrrnt.minute() || timeCurrrnt.hour())){
        timeNew = timeOld.addSecs(-1);
        ui->timeSurplus->setTime(timeNew);
        this->timeCurrrnt = timeNew;
    }
    else {
        timer->stop();  //00:00:00时停止计时
        ui->timeSurplus->setTime(timeOld);
        this->timeCurrrnt = timeOld;
        emit timerZeroSignal();
    }
}

void Hint::hintShow(QTime timeOld)
{

    timeCurrrnt = timeOld;
    ui->timeSurplus->setTime(timeOld);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(countdown())); //定时器
    timer->start(1000); //计时开始
    this->show();

}

void Hint::hintClose()
{
    this->close();
}


