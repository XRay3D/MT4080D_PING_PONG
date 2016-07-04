#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rele(this)
    , port(this)
    , timerId(0)
{
    ui->setupUi(this);
    connect(&rele, &TESTER::ReadyReadSignal, ui->lineEdit, &QLineEdit::setText);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts()) {
        ui->comboBox->addItem(info.portName());
        ui->comboBox_2->addItem(info.portName());
    }
    readSettings();
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString& arg1)
{
    if (timerId != 0) {
        killTimer(timerId);
    }
    qDebug() << "comboBox_2" << arg1;
    port.setBaudRate(9600);
    port.setParity(QSerialPort::NoParity);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.setPortName(arg1);

    if (!port.open(TESTER::WriteOnly)) {
        qDebug() << "open err";
    }
    else {
        timerId = startTimer(100);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString& arg1)
{
    qDebug() << "comboBox" << arg1;
    rele.close();
    rele.setPortName(arg1);
    if (!rele.open(TESTER::ReadWrite))
        qDebug() << "open err";
}

void MainWindow::writeSettings()
{
    QSettings settings("XrSoft", "MT4080D_PING_PONG");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("comboBox", ui->comboBox->currentIndex());
    settings.setValue("comboBox_2", ui->comboBox_2->currentIndex());
    settings.setValue("doubleSpinBox", ui->doubleSpinBox->value());
    settings.setValue("doubleSpinBox_2", ui->doubleSpinBox_2->value());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("XrSoft", "MT4080D_PING_PONG");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    ui->comboBox->setCurrentIndex(settings.value("comboBox").toInt());
    ui->comboBox_2->setCurrentIndex(settings.value("comboBox_2").toInt());
    ui->doubleSpinBox->setValue(settings.value("doubleSpinBox").toDouble());
    ui->doubleSpinBox_2->setValue(settings.value("doubleSpinBox_2").toDouble());
    settings.endGroup();
}

void MainWindow::timerEvent(QTimerEvent* TimerEvent)
{
    QByteArray data;
    int tmp = 0;
    float val = ui->doubleSpinBox->value() + ui->doubleSpinBox_2->value() * (float(qrand()) / RAND_MAX);
    ui->lineEdit_2->setText(QString("%1").arg(val));

    if (TimerEvent->timerId() == timerId) {
        data.clear();
        data.append(2);
        data.append(1);
        data.append(QByteArray().fromRawData((char*)&val, 4));
        foreach (char var, data) {
            tmp += var;
        }
        data.append(256 - (tmp & 0xFF));
        if (port.isOpen()) {
            port.write(data);
        }
    }
}
