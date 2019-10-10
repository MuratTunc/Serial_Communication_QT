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
    this->Write_Data_COMPORT(Start_SESSION);
    this->Write_Data_COMPORT(Pattern_Green);


}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
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

    connect(serial, SIGNAL(readyRead()) , this, SLOT(serialReceived()) );

    Open_Connection=true;
    this->Bytes_Received.clear();
    //qDebug("1-OPEN COMPORT OK");
    return;

}


void MainWindow::Write_Data_COMPORT(const QByteArray &data)
{
    if (Open_Connection)
    {
        serial->write(data);
        while(serial->waitForBytesWritten(10));
    }
    else
    {
        qDebug() << "SERIAL PORT - NOT OPENED" << "error code = " << serial->error();
        qDebug() << "ERROR INFO: = " << serial->errorString();
    }
    return;
}


void MainWindow::serialReceived()
{
    serial->flush();
    //qDebug() << "bytesAvailable: = " << size;
    //qDebug() << "isReadable(): = " << serial->isReadable();

    if(serial->bytesAvailable()){
        Bytes_Received.append(serial->readAll());
        ui->plainTextEdit_HEX_FORMAT-> appendPlainText( (Bytes_Received.toHex() ).toUpper() );
    }
    //qDebug() << "TOTAL BYTES= " << ((Bytes_Received.toHex() ).toUpper());

    /*
    forever {
    Bytes_Received= serial->readAll();
    if (serial->bytesAvailable() == 0 && !serial->waitForReadyRead(5))
        break;
    }


    Data_Received_HEX=(Bytes_Received.toHex()).toUpper();

    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
    Data_Received_STRING = codec->toUnicode(Bytes_Received);

    ui->label->setText(Data_Received_HEX);
    qDebug() << "3-Received Response is: " << Bytes_Received;

    ui->plainTextEdit_HEX_FORMAT->appendPlainText(Data_Received_HEX);
    ui->plainTextEdit_STRING_FORMAT->appendPlainText(Data_Received_STRING);

    */
    return;
}
