#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QtCore/QtGlobal>
#include <QString>
#include <QTextCodec>
#include <QPlainTextEdit>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    serial = new QSerialPort(this);
    this->OpenComPort();
    this->Write_Data_COMPORT(Get_SW_VERSION);

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


void MainWindow::serialReceived()
{
    serial->flush();
    Bytes_Received= serial->readAll();
    while( serial->waitForReadyRead(100))
         Bytes_Received=serial->readAll();



    Data_Received_HEX=Bytes_Received.toHex();
    Data_Received_HEX=Data_Received_HEX.toUpper();

    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
    Data_Received_STRING = codec->toUnicode(Bytes_Received);

    ui->label->setText(Data_Received_HEX);
    qDebug() << "3-Received Response is: " << Bytes_Received;

    ui->plainTextEdit_HEX_FORMAT->appendPlainText(Data_Received_HEX);
    ui->plainTextEdit_STRING_FORMAT->appendPlainText(Data_Received_STRING);

}

