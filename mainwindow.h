#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    const QByteArray Pattern_Green = QByteArray("\xE0\x05\x31\x02\xE7",5);
    const QByteArray Pattern_Green2 = QByteArray("\xE0\x05\x31\x05\xE4",5);
    const QByteArray Get_SW_VERSION = QByteArray("\xE0\x04\x36\xE5",4);
    const QByteArray Start_SESSION = QByteArray("\xE0\x04\x01\x1A",4);
    bool Open_Connection = false;


    void Write_Data_COMPORT(const QByteArray &data);

    ~MainWindow();

private slots:
    void Received_From_COMPORT();
    void serialReceived();
    void OpenComPort();


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
