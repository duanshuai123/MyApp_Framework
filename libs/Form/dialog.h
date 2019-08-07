#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <geoEngine.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void slotButtonClick();
    void slotOnTimeOutPut();
    void slotChangeProcessAndLabel(const int& dValue,const QString& sValue);

private:
    Ui::Dialog *ui;
    QTimer* m_pTimer;// ding shi  qi
};

#endif // DIALOG_H
