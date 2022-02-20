#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>
#include <QTimer>
#include <QDateTime>


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
    void on_pushButton_clicked(bool checked);
    void setAixsSize();
    void mouse_view(QPoint p);
    void timeUpdate();

private:
    Ui::MainWindow *ui;
    QLineSeries *curSeries;
    QValueAxis *curAxis;
    QChart *m_chart;
    QTimer * timer;
    void createChart();
    void prepareData();
    void updateFromChart();
};
#endif // MAINWINDOW_H
