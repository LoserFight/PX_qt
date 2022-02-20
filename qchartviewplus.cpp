#include "qchartviewplus.h"
#include "callout.h"

void QChartViewPlus::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p= event->pos();
    emit mouseMovePoint(p);
    QChartView::mouseMoveEvent(event);
}

QChartViewPlus::QChartViewPlus(QWidget* parent):QChartView(parent)
{
    this->setMouseTracking(true);
    this->setDragMode(QGraphicsView::RubberBandDrag);
    //setAcceptHoverEvents(true);
}

void QChartViewPlus::keepCallout()
{
//    QPointF p=m_tooltip->AnchorPs();
//    double key=p.x()*128.0+p.y();
//    if(m_set.contains(key)==false){
//        m_set.insert(key);
        m_callouts.append(m_tooltip);
        m_tooltip = new Callout(this->chart());
//    }
//    else{
//        for(auto & ne:m_callouts){
//            QPointF p1=ne->AnchorPs();
//            if(p1.x()==p.x()&&p1.y()==p.y()){
//                ne->hide();
//            }
//            m_set.erase(m_set.find(key));
//            m_tooltip = new Callout(this->chart());
//        }
//    }
}

void QChartViewPlus::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(this->chart());

    if (state) {
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}

