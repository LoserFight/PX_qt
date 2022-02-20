#ifndef QCHARTVIEWPLUS_H
#define QCHARTVIEWPLUS_H

#include <QChartView>
#include "callout.h"
//class Callout;

class QChartViewPlus : public QChartView
{
    Q_OBJECT
    QPoint beginPoint;
    QPoint endPoint;
    Callout *m_tooltip;
    QList<Callout *> m_callouts;
    QSet<double> m_set;
protected:
    void mouseMoveEvent(QMouseEvent *event);
public:
    QChartViewPlus(QWidget* parent);
    ~QChartViewPlus(){};
signals:
    void mouseMovePoint(QPoint p);
public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);


};

#endif // QCHARTVIEWPLUS_H
