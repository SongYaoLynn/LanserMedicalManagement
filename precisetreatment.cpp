#include "precisetreatment.h"
#include "ui_precisetreatment.h"
#include <QStackedLayout>
#include <QVBoxLayout>

PreciseTreatment::PreciseTreatment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreciseTreatment)
{
    ui->setupUi(this);
    preciseTreatmentInit();
    //test------------------------------------
//    qDebug("%s\n", name.toLatin1().data());
//    ui->userSetComboBox->addItem(name);
    //--------------------------------------

    userNew = new UserNew;
    userNameNew = new UserNameNew;
    userEdit = new UserEdit;
    saveToU = new SaveToU;
    saveUDataToLocal = new SaveUDataToLocal;
    // 页面转换
    stackLayout = new QStackedLayout;
    stackLayout->addWidget(this);
    stackLayout->addWidget(userNew);
    stackLayout->addWidget(userNameNew);
    stackLayout->addWidget(userEdit);
    stackLayout->addWidget(saveToU);
    stackLayout->addWidget(saveUDataToLocal);

    connect(this, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int)));    //精准治疗主界面 0
    connect(userNew, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //新建用户设置 1
    connect(userNameNew, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //用户名输入 2
    connect(userEdit, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //编辑 3
    connect(saveToU, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //保存到U盘 4
    connect(saveUDataToLocal, SIGNAL(changeDispalySignal(int)), this, SLOT(changeDisplay(int))); //保存U盘数据到本地 5



}

PreciseTreatment::~PreciseTreatment()
{
    delete ui;
}

void PreciseTreatment::userSavedSetting(QString username)
{
    dlg = new QDialog(this);
    dlg->setWindowTitle(username);
    dlg->resize(200,80);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    dlg->setWindowFlags(flags); //去除弹出框右上角的问号
    // 控件
    QLabel *label = new QLabel;
    label->setText("请选择治疗区域");
    areaBtn1 = new QPushButton(tr("1"));
    areaBtn2 = new QPushButton(tr("2"));
    areaBtn3 = new QPushButton(tr("3"));
    submitBtn = new QPushButton(tr("确认"));
    cancelBtn = new QPushButton(tr("取消"));
    areaBtn1->setFixedWidth(30);
    areaBtn2->setFixedWidth(30);
    areaBtn3->setFixedWidth(30);
    //栅格布局
    QGridLayout *gridLayout = new QGridLayout(dlg);
    gridLayout->addWidget(label, 0, 0, 1, 3, Qt::AlignCenter | Qt::AlignVCenter);
    gridLayout->addWidget(areaBtn1, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
    gridLayout->addWidget(areaBtn2, 1, 1, 1, 1, Qt::AlignCenter | Qt::AlignVCenter);
    gridLayout->addWidget(areaBtn3, 1, 2, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    gridLayout->addWidget(submitBtn, 2, 0, 1, 1);
    gridLayout->addWidget(cancelBtn, 2, 2, 1, 1);
    //控件响应
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(areaCancel()));    //  关闭弹窗
    // 三个治疗区域的选择
    connect(areaBtn1, SIGNAL(clicked()), this, SLOT(areaGetOne()));
    connect(areaBtn2, SIGNAL(clicked()), this, SLOT(areaGetTwo()));
    connect(areaBtn3, SIGNAL(clicked()), this, SLOT(areaGetThree()));
    connect(this, SIGNAL(areaChooseSignal(int)), this, SLOT(areaChoose(int)));
    // 确定
    connect(submitBtn, SIGNAL(clicked()), this, SLOT(areaSubmit()));

    dlg->setModal(true);
    dlg->show();
}

void PreciseTreatment::changeDisplay(int index)
{
    stackLayout->setCurrentIndex(index);
}



void PreciseTreatment::on_userSetComboBox_activated(int index)
{
    qDebug("%d\n", index);
    if (index < 4)
    {
        switch (index) {
        case 0:
            emit changeDispalySignal(1);
            break;
        case 1:
            emit changeDispalySignal(3);
            break;
        case 2:
            emit changeDispalySignal(4);
            break;
        case 3:
            emit changeDispalySignal(5);
        default:
            break;
        }

    }
    else
    {
        userSavedSetting(ui->userSetComboBox->currentText());   //  已存储的用户设置
    }
}

void PreciseTreatment::areaGetOne()
{
    emit areaChooseSignal(1);
}

void PreciseTreatment::areaGetTwo()
{
    emit areaChooseSignal(2);
}

void PreciseTreatment::areaGetThree()
{
    emit areaChooseSignal(3);
}

void PreciseTreatment::areaSubmit()
{
    if(area > 0){

        //执行相关操作，area即所选的治疗区域
        //..........................
    }
    else {
        // 弹出警告框
        //..........................
    }
    qDebug("%d", area);
}

void PreciseTreatment::areaCancel()
{
    dlg->close();
}

void PreciseTreatment::areaChoose(int area)
{
    this->area = area;
    qDebug("%d", this->area);
}

void PreciseTreatment::preciseTreatmentInit()
{
    ui->text1->setText(tr("测试文字1"));
    ui->text2->setText(tr("测试文字2"));
}

void PreciseTreatment::on_clearBtn_clicked()
{
    ui->text2->setText(tr("0"));
}

void PreciseTreatment::on_test_clicked()
{
    warning = new Warning;
    warning->warningShow(tr("警告测试"));
}
