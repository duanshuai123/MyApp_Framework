#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slotButtonClick()));

    geoEngine* pGeoEngine = geoEngine::Instance();
    QObject::connect(pGeoEngine,SIGNAL(sigProcessAndLabel(const int&,const QString&)),this,SLOT(slotChangeProcessAndLabel(const int&,const QString&)));

    //test
     m_pTimer = new QTimer(this);
     m_pTimer->setInterval(200);
     connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slotOnTimeOutPut()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slotChangeProcessAndLabel(const int& dValue,const QString& sValue)
{
    ui->progressBar->setValue(dValue);
    ui->label->setText(sValue);
}

void Dialog::slotButtonClick()
{
    m_pTimer->start();
}

void Dialog::slotOnTimeOutPut()
{
   static int iii = 0;
   iii++;
   geoEngine* pGeoEngine = geoEngine::Instance();
   QString strLabel = "process is %" + QString::number(iii);
//定时器每割200毫秒，调用一次GeoEngine的槽函数slotProcessAndLabel，在槽函数里激发sigProcessAndLabel信号，
//凡是与该信号绑定的都会响应，而Dialog的构造函数里（11-12行），信号绑定了slotChangeProcessAndLabel,改变滚动条与label的值
//其核心就是利用geoEngine进行消息传递，因为geoEngine各个库各个类都可以访问，是个稳定不变的单例。
   pGeoEngine->slotProcessAndLabel(iii,strLabel); 
   if(iii==100)
       iii = 0;
}
