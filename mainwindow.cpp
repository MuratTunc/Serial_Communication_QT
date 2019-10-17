 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QString>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialTextReady(QString str)
{
    ui->plainTextEdit_STRING_FORMAT->appendPlainText(str);
    ui->plainTextEdit_STRING_FORMAT->update();
}

void MainWindow::serialHEXReady(QString str)
{
    ui->plainTextEdit_HEX_FORMAT->appendPlainText(str);
    ui->plainTextEdit_HEX_FORMAT->update();
}

