#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QThread>
#include <QSerialPort>
#include <QTextCodec>

#include "interfaces.h"

class AutoTest: public QThread
{
protected:
    const QByteArray Pattern_Green = QByteArray("\xE0\x05\x31\x02\xE7",5);
    const QByteArray Pattern_Green2 = QByteArray("\xE0\x05\x31\x05\xE4",5);
    const QByteArray Get_SW_VERSION = QByteArray("\xE0\x04\x36\xE5",4);
    const QByteArray Start_SESSION = QByteArray("\xE0\x04\x01\x1A",4);
    const QByteArray Check_BER = QByteArray("\xE0\x04\x63\xB8 ",4);
    const QByteArray Check_VIDEO = QByteArray("\xE0\x0A\x10\x00\x48\0x02\x1C\x20\x01\x7E",10);

    const QByteArray HDMI1_Source_SWITCH = QByteArray("\xE0\x05\x0A\x08\x08",5);
    const QByteArray HDMI2_Source_SWITCH = QByteArray("\xE0\x05\x0A\x09\x07",5);
    const QByteArray HDMI3_Source_SWITCH = QByteArray("\xE0\x05\x0A\x0A\x06",5);
    const QByteArray DVBC_Source_SWITCH  = QByteArray("\xE0\x05\x0A\x13\xFD",5);
    const QByteArray DVBS_Source_SWITCH  = QByteArray("\xE0\x05\x0A\x14\xFC",5);

    QSerialPort serial;
    iSerialTextReceiver* pReceiver;

    bool IsOKtoSend = true;


    bool Open_Connection = false;
    bool IsTvAlive = false;
    bool RETURN_LEN_FLAG = false;
    QByteArray Bytes_Received;
    QString Bytes_Received_HEX =" ";
    QString Bytes_Received_STRING=" ";
    void Boot_Up_StartSession();
    void Get_LEN();

    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");

    QString Command_Name =" ";
    uint Command_Return_Length = 0;
    uint count=0;
    uint lim=2;


    bool openPort();
    void writeData(QByteArray data);
    virtual void run();

public:
    AutoTest( iSerialTextReceiver* receiver );
    ~AutoTest();

    void startAutoTest();

private slots:
    void serialReceived();


};

#endif // AUTOTEST_H
