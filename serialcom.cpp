#include "serialcom.h"

serialCom::serialCom(QObject *parent,int times)
    : QObject{parent}
{
    com_timer=0;
    m_SerialPort=0;
    timeO=times;
    nameP="COM5";
    Brate=115200;
    bitsS=QSerialPort::Data8;
    stopB=QSerialPort::OneStop;
    parity=QSerialPort::NoParity;
    contr=QSerialPort::HardwareControl;


}

serialCom::~serialCom()
{
    delete m_SerialPort;
    delete com_timer;

}

void serialCom::String2Hex(QString str, QByteArray &w)
{
     int hexdata,lowhexdata;
     int hexdatalen = 0;
     int len = str.length();
     w.resize(len / 2);
     char lstr,hstr;
     for (int i = 0; i < len; ) {
      hstr = str[i].toLatin1();
      if (hstr == ' ') {
       ++i;
       continue;
      }
      ++i;
      if (i >= len) break;
      lstr = str[i].toLatin1();
      hexdata = convertHexChar(hstr);
      lowhexdata = convertHexChar(lstr);
      if ((hexdata == 16) || (lowhexdata == 16))
       break;
      else
       hexdata = hexdata*16 + lowhexdata;
      ++i;
      w[hexdatalen] = (char)hexdata;
      ++hexdatalen;
     }
     w.resize(hexdatalen);
}

char serialCom::convertHexChar(char ch)
{
    if ((ch >= '0') && (ch <= '9'))
     return ch - 0x30;
    else if ((ch >= 'A') && (ch <= 'F'))
     return ch - 'A' + 10;
    else if ((ch >= 'a') && (ch <= 'f'))
     return ch - 'a' + 10;
    else return ch - ch;
}

void serialCom::init()
{
    if(m_SerialPort==0){
    m_SerialPort=new QSerialPort;}
    if(com_timer==0){
    com_timer= new QTimer;
    connect(m_SerialPort, SIGNAL(readyRead()),this, SLOT(read_recv()));
    connect(com_timer,SIGNAL(timeout()),this,SLOT(writeto()));
    }

    m_SerialPort->setPortName(nameP);
    m_SerialPort->setBaudRate(Brate);
    m_SerialPort->setDataBits(bitsS);
    m_SerialPort->setStopBits(stopB);
    m_SerialPort->setParity(parity);
    m_SerialPort->setFlowControl(contr);//the flow control used.


}

void serialCom::read_recv()
{
    QByteArray data = m_SerialPort->readAll();
    emit read_data(data);
}

void serialCom::writeto()
{
    m_SerialPort->write(writeData);
}

void serialCom::closePort()
{
    m_SerialPort->close();
    com_timer->stop();
}

void serialCom::openPort()
{
    if(m_SerialPort->open(QIODeviceBase::ReadWrite)){
        qDebug() << "Port have been opened";
        com_timer->start(timeO);
    }
    else{
        qDebug() <<"open Port failed";
    }
}

