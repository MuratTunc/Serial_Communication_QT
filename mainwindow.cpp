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
    /*
    this->Write_Data_COMPORT(Get_SW_VERSION);
    this->Write_Data_COMPORT(Start_SESSION);
    this->Write_Data_COMPORT(Pattern_Green);
    */

    //this->Write_Data_COMPORT(Start_SESSION);
    this->Boot_Up_StartSession();


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
        qDebug() << "SERIAL PORT - NOT OPENED" << "error code = " << serial->error();
        qDebug() << "ERROR INFO: = " << serial->errorString();
        delete serial;
        serial = NULL;
        return;
    }

    //CONNECT**********************************************************************

    connect(serial, SIGNAL(readyRead()) , this, SLOT(serialReceived()) );

    Open_Connection=true;
    this->Bytes_Received.clear();

}


void MainWindow::Write_Data_COMPORT(const QByteArray &data)
{
    this->Bytes_Received.clear();
    serial->write(data);
    while(serial->waitForBytesWritten(10));


}


void MainWindow::serialReceived()
{
    serial->flush();
    if(serial->bytesAvailable()==17){
        Bytes_Received.append(serial->readAll() );
        ui->plainTextEdit_HEX_FORMAT-> appendPlainText(  (Bytes_Received.toHex() ).toUpper() );
        //ui->plainTextEdit_STRING_FORMAT->appendPlainText( codec->toUnicode(Bytes_Received)   );
        qDebug() << "Bytes_Received: = " << Bytes_Received;
        qDebug() << "*****************";
    }

}

void MainWindow::Boot_Up_StartSession(){

    while(!IsTvAlive){
        this->Write_Data_COMPORT(Get_SW_VERSION);

        if( Bytes_Received == "xE0\x04\x00\x1B"){
            IsTvAlive = true;
            ui->plainTextEdit_STRING_FORMAT->appendPlainText("TV IS ALIVE...");
        }
        QThread::msleep(10);
    }

}
