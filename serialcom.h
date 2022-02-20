#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QObject>

class serialCom : public QObject
{
    Q_OBJECT
public:
    explicit serialCom(QObject *parent = nullptr);

signals:

};

#endif // SERIALCOM_H
