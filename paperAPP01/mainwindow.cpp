#include <stdlib.h>
#include <sstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/favicon.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_openPort_clicked()
{
    QSerialPort *serialPort = new QSerialPort(this);
    /* 串口设置 */
    serialPort->setPortName(ui->BoxPort->currentText());
    serialPort->setBaudRate(ui->BoxBaudRate->currentText().toInt());
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);

    /* 打开串口提示框 */
    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened successfully!";
        ui->openPort->setText("打开成功");
        ui->openPort->setStyleSheet("background-color: #7ebc59;");
        connect(serialPort, &QSerialPort::readyRead, this, [=](){
            readData(serialPort);
        });
    } else {
        qDebug() << "Failed to open serial port!";
    }
}


void MainWindow::on_FindPort_clicked()
{
    QStringList serialNamePort;
    foreach (const QSerialPortInfo &inf0, QSerialPortInfo::availablePorts()) {
        serialNamePort<<inf0.portName();
    }
    ui->BoxPort->addItems(serialNamePort);
}

void MainWindow::readData(QSerialPort *serialPort)
{
    QByteArray data = serialPort->readAll();
    std::string str = data.toStdString();
    if (str[0]== '$'){
        std::istringstream ss(str.substr(1));
        int num;
        ss >> num;
        // process or display the received data
        ui->screen->display(num);
    }
    else {
        ui->messageBar->setText(data);
    }
}

