#include "autotest.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QtCore/QtGlobal>
#include <QString>
#include <QTextCodec>
#include <QPlainTextEdit>
#include <QTimer>

AutoTest::AutoTest(iSerialTextReceiver *receiver)
{
    pReceiver = receiver;
    IsTvAlive = false;
}

AutoTest::~AutoTest()
{
    serial.close();
}

void AutoTest::run()
{
    startAutoTest();
}

void AutoTest::startAutoTest()
{
    if( openPort() )
    {

         //Boot_Up_StartSession();
        writeData(Start_SESSION);
        //QThread::msleep(500);

        //writeData(Get_SW_VERSION);
#if 0
        writeData(HDMI1_Source_SWITCH);
        QThread::msleep(5000);
        writeData(DVBS_Source_SWITCH);
        QThread::msleep(8000);
        writeData(HDMI2_Source_SWITCH);
        QThread::msleep(8000);
        writeData(DVBC_Source_SWITCH);
#endif

    }
}

bool AutoTest::openPort()
{

    serial.setPortName("/dev/ttyS0");

    if (!serial.setBaudRate(QSerialPort::Baud115200) ||
        !serial.setDataBits(QSerialPort::Data8) ||
        !serial.setParity(QSerialPort::NoParity) ||
        !serial.setStopBits(QSerialPort::OneStop) ||
        !serial.setFlowControl(QSerialPort::NoFlowControl)) {

        qDebug() << "ERROR Failed to setup serial port!!!";
        return false;
    }

    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Error Failed to open serial port!!!";
        qDebug() << "SERIAL PORT - NOT OPENED" << "error code = " << serial.error();
        qDebug() << "ERROR INFO: = " << serial.errorString();
        return false;
    }

    //CONNECT**********************************************************************

    serial.clear();
    connect(&serial, &QSerialPort::readyRead , this, &AutoTest::serialReceived );

    Open_Connection=true;
    Bytes_Received.clear();
    count=0;
    lim=2;
    return true;
}


void AutoTest::writeData(QByteArray data)
{
    Bytes_Received.clear();
    serial.write(data);
    while(serial.waitForBytesWritten(100));
    serial.flush();
}


void AutoTest::serialReceived()
{

    while(serial.bytesAvailable() && count<lim)
    {
        char c;
        serial.read(&c,1);
        Bytes_Received.append(c);

        if(count==1)
            lim+=(c-2);

        count++;
    }

    if( count==lim )
    {
        count=0;
        lim=2;
        Bytes_Received.append('\0');
        pReceiver->serialHEXReady( (Bytes_Received.toHex() ).toUpper() );
        pReceiver->serialTextReady( codec->toUnicode(Bytes_Received) );
        IsOKtoSend=true;
    }

}

void AutoTest::Boot_Up_StartSession(){
    while(!IsTvAlive){
        writeData(Start_SESSION);

        if( codec->toUnicode(Bytes_Received)=="E004001B"){
            IsTvAlive = true;
            pReceiver->serialTextReady("TV IS ALIVE...");
            qDebug() << "TV FIRST CHECK...";
        }
    }

}


