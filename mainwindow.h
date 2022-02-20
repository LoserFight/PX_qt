#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>
#include <QTimer>
#include <QDateTime>
#include "serialcom.h"
#include "comsetdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void setAixsSize();
    void mouse_view(QPoint p);
    void timeUpdate();
    void recvFromS(QByteArray b);
    void wrthread();
    void stopCom();
signals:
    void printData(QByteArray b);
    void openPort();
    void closePort();
private:
    Ui::MainWindow *ui;
    QLineSeries *curSeries;
    QValueAxis *curAxis;
    QChart *m_chart;
    QTimer * timer;
    serialCom* m_com;
    QThread *readWriteThread;
    comSetDialog *f;
    void createChart();
    void prepareData();
    void updateFromChart();
};
#endif // MAINWINDOW_H
