#ifndef COMSETDIALOG_H
#define COMSETDIALOG_H

#include <QDialog>
#include"serialcom.h"

namespace Ui {
class comSetDialog;
}

class comSetDialog : public QDialog
{
    Q_OBJECT

public:
    serialCom* m_port;
    explicit comSetDialog(serialCom *port,QWidget *parent = nullptr);
    explicit comSetDialog(QWidget *parent = nullptr);
    ~comSetDialog();
    void updatePort();
    void findSerial();
public slots:
    void printTxt(QByteArray tmp);
    void on_connectBtn_clicked(bool checked);
    void checkCOM();
signals:
    void beginConnect();
    void closeConnect();
private:
    Ui::comSetDialog *ui;
    QTimer* TimerCheck;

};

#endif // COMSETDIALOG_H
