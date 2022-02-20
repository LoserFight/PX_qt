#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QObject>
#include <QtSerialPort>

class serialCom : public QObject
{
    Q_OBJECT
    QSerialPort* m_SerialPort;
    QTimer * com_timer;
    int timeO;

public:
    qint32 Brate;
    QString nameP;
    enum QSerialPort::DataBits bitsS;
    enum QSerialPort::StopBits stopB;
    enum QSerialPort::Parity parity;
    enum QSerialPort::FlowControl contr;
    QByteArray writeData;
    explicit serialCom(QObject *parent = nullptr,int times=1000);
    ~serialCom();
    void String2Hex(QString str,QByteArray &w);
    char convertHexChar(char ch);


public slots:
    void init();
    void read_recv();
    void writeto();
    void closePort();
    void openPort();

signals:
    void read_data(QByteArray tmp);

};


#endif // SERIALCOM_H
