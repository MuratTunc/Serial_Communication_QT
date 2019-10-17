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

    //this->Write_Data_COMPORT(Get_SW_VERSION);
    //this->Write_Data_COMPORT(Start_SESSION);
    //this->Write_Data_COMPORT(Pattern_Green);

    //this->Write_Data_COMPORT(Pattern_Green2);


    this->Write_Data_COMPORT(HDMI1_Source_SWITCH);
    QThread::msleep(5000);
    this->Write_Data_COMPORT(DVBS_Source_SWITCH);
    QThread::msleep(8000);
    this->Write_Data_COMPORT(HDMI2_Source_SWITCH);
    QThread::msleep(8000);
    this->Write_Data_COMPORT(DVBC_Source_SWITCH);


    //this->Boot_Up_StartSession();


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
    qDebug() << serial->errorString();


}

void MainWindow::serialReceived()
{
    serial->flush();
    qDebug() << "serial->bytesAvailable()= " << serial->bytesAvailable() ;

    /*if( serial->bytesAvailable() < 4 && serial->waitForReadyRead(20) ){
        Bytes_Received.append(serial->readAll() );
        qDebug() << "Bytes_Received: = " << Bytes_Received;
        RETURN_LEN_FLAG=true;
    }


    if( RETURN_LEN_FLAG && serial->bytesAvailable() >1 ){
        if(Bytes_Received.at(0)==224){
            qDebug() << "Bytes_Received.at(1) = "<<(int) (Bytes_Received.at(1) );
            Command_Return_Length = (int)Bytes_Received.at(1);

        }

    }

    */
    if( serial->bytesAvailable() < 20 || serial->waitForReadyRead(100      ) ){
        Bytes_Received.append(serial->readAll() );
        qDebug() << "Bytes_Received: = " << Bytes_Received;
    }
    ui->plainTextEdit_HEX_FORMAT-> appendPlainText(  (Bytes_Received.toHex() ).toUpper() );
    ui->plainTextEdit_STRING_FORMAT->appendPlainText( codec->toUnicode(Bytes_Received)   );

}


void MainWindow::Boot_Up_StartSession(){
    while(!IsTvAlive){
        this->Write_Data_COMPORT(Start_SESSION);

        if( Bytes_Received.length()==4 && Bytes_Received.at(2)=='\x00'){
            IsTvAlive = true;
            ui->plainTextEdit_STRING_FORMAT->appendPlainText("TV IS ALIVE...");
        }
    }

}

