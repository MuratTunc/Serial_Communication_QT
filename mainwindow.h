#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfaces.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public iSerialTextReceiver
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    virtual void serialTextReady(QString str);
    virtual void serialHEXReady(QString str);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
