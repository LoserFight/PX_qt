#include "comsetdialog.h"
#include "ui_comsetdialog.h"

comSetDialog::comSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::comSetDialog)
{
    ui->setupUi(this);

}

comSetDialog::comSetDialog(serialCom *port, QWidget *parent):
    QDialog(parent),
    ui(new Ui::comSetDialog)
{

    ui->setupUi(this);
    m_port=port;
    findSerial();
    TimerCheck= new QTimer;
    connect(TimerCheck,SIGNAL(timeout()),this,SLOT(checkCOM()));
    TimerCheck->start(5000);


}

void comSetDialog::updatePort()
{
    if(ui->comboBox_3->currentText()=="115200"){
        m_port->Brate=115200;
    }
    else if(ui->comboBox_3->currentText()=="57600"){
        m_port->Brate=57600;
    }
    else if(ui->comboBox_3->currentText()=="37400"){
        m_port->Brate=37400;
    }
    else if(ui->comboBox_3->currentText()=="19200"){
        m_port->Brate=19200;
    }
    else if(ui->comboBox_3->currentText()=="4800"){
        m_port->Brate=4800;
    }
    else if(ui->comboBox_3->currentText()=="2400"){
        m_port->Brate=2400;
    }

    if(ui->comboBox_4->currentText()=="8"){
        m_port->bitsS=QSerialPort::Data8;
    }
    else if(ui->comboBox_4->currentText()=="7"){
        m_port->bitsS=QSerialPort::Data7;
    }
    else if(ui->comboBox_4->currentText()=="6"){
        m_port->bitsS=QSerialPort::Data6;
    }
    else if(ui->comboBox_4->currentText()=="5"){
        m_port->bitsS=QSerialPort::Data5;
    }

    if (ui->comboBox_5->currentText() == "1")
     m_port->stopB=QSerialPort::OneStop;
    else if (ui->comboBox_5->currentText() == "1.5")
     m_port->stopB=QSerialPort::OneAndHalfStop;
    else if (ui->comboBox_5->currentText() == "2")
     m_port->stopB=QSerialPort::TwoStop;


    if(ui->comboBox_10->currentText()=="off"){
        m_port->contr=QSerialPort::NoFlowControl;

    }
    else if(ui->comboBox_10->currentText()=="off"){
        m_port->contr=QSerialPort::HardwareControl;

    }
    else if(ui->comboBox_10->currentText()=="xonxoff"){
        m_port->contr=QSerialPort::SoftwareControl;
    }
    //m_port->writeData.clear();
    QString dataToWrite=ui->textEdit->toPlainText();
    if(dataToWrite.length()%2==1){
        dataToWrite.insert(dataToWrite.length()-1,'0');
    }
    m_port->String2Hex(dataToWrite,m_port->writeData);
    m_port->nameP=ui->comboBox_2->currentText();

}

void comSetDialog::findSerial()
{
    ui->comboBox_2->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
       {
           QSerialPort tempSer;
           tempSer.setPort(info);
           if(tempSer.open(QIODevice::ReadWrite))
           {
               ui->comboBox_2->addItem(tempSer.portName());
               tempSer.close();
           }
       }

}

void comSetDialog::printTxt(QByteArray tmp)
{
    QString buff;
    for(int i=0;i<tmp.count();i++){
        QString s;
        s.asprintf("0x%02x, ",(unsigned char)tmp.at(i));
        buff+=s;
    }
    buff+="\n";
    //ui->textBrowser->setText(ui->textBrowser->document()->toPlainText()+buff);
    ui->textBrowser->textCursor().insertText(buff);
    ui->textBrowser->moveCursor(QTextCursor::End);

}



comSetDialog::~comSetDialog()
{
    delete ui;
    delete TimerCheck;
}



void comSetDialog::on_connectBtn_clicked(bool checked)
{
    if(checked){
        TimerCheck->stop();
        ui->connectBtn->setText("disconnect");
        updatePort();
        emit beginConnect();

    }
    else{
        TimerCheck->start(5000);
        ui->connectBtn->setText("connect");
        emit closeConnect();
    }
}

void comSetDialog::checkCOM()
{
    findSerial();

}

