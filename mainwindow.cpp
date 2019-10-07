#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QtCore/QtGlobal>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    serial = new QSerialPort(this);
    //OPEN AND INITIALIZE COMPORT
    this->OpenComPort();
    this->Write_Data_COMPORT(Pattern_Green);
    //this->serialReceived();


}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
}

//OPEN COMPORT
void MainWindow::OpenComPort()
{

    serial->setPortName("/dev/ttyS0");

    if (!serial->setBaudRate(QSerialPort::Baud115200) ||
        !serial->setDataBits(QSerialPort::Data8) ||
        !serial->setParity(QSerialPort::NoParity) ||
        !serial->setStopBits(QSerialPort::OneStop) ||
        !serial->setFlowControl(QSerialPort::NoFlowControl)) {

        qDebug() << "ERROR Failed to setup serial port!!!";
        delete serial;
        serial = NULL;
        return;
    }

    if (!serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Error Failed to open serial port!!!";
        delete serial;
        serial = NULL;
        return;
    }

    //CONNECT**********************************************************************
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
    serial->clear();
    serial->flush();
    Open_Connection=true;
    //qDebug("1-OPEN COMPORT OK");

}


void MainWindow::Write_Data_COMPORT(const QByteArray &data)
{
    if (Open_Connection)
    {
        serial->write(data);
        //qDebug("2-DATA SENT TO COMPORT");
    }
    else
    {
        qDebug() << "SERIAL PORT - NOT OPENED" << "error code = " << serial->error();
        qDebug() << "ERROR INFO: = " << serial->errorString();
    }
}

void MainWindow::Received_From_COMPORT(){



    QByteArray Read_Data_Array;
    QString s_data;
    Read_Data_Array=serial->readAll();
    qDebug()<<"Data Received:"<<Read_Data_Array;

    s_data=Read_Data_Array.toHex();
    s_data=s_data.toUpper();

    //s_data = QString::fromStdString(Read_Data_Array.toStdString());

    ui->label->setText(s_data);

}


void MainWindow::serialReceived()
{
    serial->flush();
    QByteArray Bytes_Array = serial->readAll();
    while( serial->waitForReadyRead(1000))
        Bytes_Array=serial->readAll();



    ui->label->setText(Bytes_Array.toHex().toUpper());
    qDebug() << "3-Received Response is: " << Bytes_Array;


    /*
    qDebug()<<"Bytes At Port"<<serial->bytesAvailable();
    serial->waitForReadyRead(1000);

    qDebug()<<"Bytes At Port"<<serial->bytesAvailable();
    serial->waitForReadyRead(1000);

    qDebug()<<"Bytes At Port"<<serial->bytesAvailable();
    serial->waitForReadyRead(1000);




    QByteArray ba;
    serial->waitForReadyRead(4000);
    //while (serial->bytesAvailable()<10 ){    //canReadLine()
        //qDebug() << "canReadLine loop ";
        ba = serial->readAll();
    //}
    ui->label->setText(ba.toHex());
    qDebug() << "Received Response is: " << ba;
    */

}

