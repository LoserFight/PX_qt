#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qchartviewplus.h"
#include<QtGlobal>

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();
    prepareData();
    updateFromChart();
    timer=new QTimer(this);
    connect(ui->radioButton,SIGNAL(clicked()),this,SLOT(setAixsSize()));
    connect(ui->radioButton_2,SIGNAL(clicked()),this,SLOT(setAixsSize()));
    connect(ui->radioButton_3,SIGNAL(clicked()),this,SLOT(setAixsSize()));
    connect(ui->radioButton_4,SIGNAL(clicked()),this,SLOT(setAixsSize()));
    connect(ui->chartView,SIGNAL(mouseMovePoint(QPoint)),this,SLOT(mouse_view(QPoint)));
    connect(curSeries, &QLineSeries::clicked, ui->chartView, &QChartViewPlus::keepCallout);
    connect(curSeries, &QLineSeries::hovered, ui->chartView, &QChartViewPlus::tooltip);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::createChart(){
    QChart *chart=new QChart();
    //chart->setTitle("F");
    chart->setAcceptHoverEvents(true);

    m_chart=chart;
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    QLineSeries *series0= new QLineSeries();
    //QLineSeries *series1= new QLineSeries();
    series0->setName("sin");
    //series1->setName("cos");
    curSeries=series0;
    m_chart->legend()->hide();
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::black);
    series0->setPen(pen);

    chart->addSeries(series0);
    QValueAxis *axisX=new QValueAxis;
    curAxis=axisX;
    axisX->setRange(0,500);
    axisX->setLabelFormat("%.1f");
    axisX->setMinorTickCount(4);
    //axisX->setTitleText("time(secs)");
    QValueAxis *axisY=new QValueAxis;
    //curAxis=axisX;
    axisY->setRange(0,100);
    axisY->setLabelFormat("%.1f");
    axisY->setMinorTickCount(4);
    //axisY->setTitleText("time(secs)");
    chart->addAxis(axisY,Qt::AlignLeft);
    chart->addAxis(axisX,Qt::AlignBottom);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);
    //ui->chartView->setMouseTracking(true);


}



void MainWindow:: prepareData(){
    QLineSeries *series0=(QLineSeries *)ui->chartView->chart()->series().at(0);
    series0->clear();
    srand(QTime::currentTime().second());
    qreal t=0,y1,intv=1;
    int cnt=200;
    for(int i=0;i<cnt;i++){
        y1=qSin(0.5*t)*25+50.0;
        series0->append(t,y1);
        t+=intv;
    }
}
void MainWindow::updateFromChart(){

}

void MainWindow::on_pushButton_clicked(bool checked)
{

}


void MainWindow::mouse_view(QPoint px)
{
    QPointF p=m_chart->mapToValue(px);
    ui->Mouse_pos->setText(QString::asprintf("(%.1f,%.1f)",p.x(),p.y()));

}

void MainWindow::timeUpdate()
{
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->timeNow->setText(str);

}


void MainWindow::setAixsSize()
{
    qreal maxi=500.0;
    if(ui->radioButton->isChecked()){
        maxi=500.0;
    }
    else if(ui->radioButton_2->isChecked()){
        maxi=1000.0;
    }
    else if(ui->radioButton_3->isChecked()){
        maxi=2000.0;
    }
    else if(ui->radioButton_4->isChecked()){
        maxi=4000.0;
    }
    QValueAxis *axisX=curAxis;
    //curAxis=axisX;
    axisX->setRange(0,maxi);
    //prepareData();
}

