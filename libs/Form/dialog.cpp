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
   pGeoEngine->slotProcessAndLabel(iii,strLabel);
   if(iii==100)
       iii = 0;
}
