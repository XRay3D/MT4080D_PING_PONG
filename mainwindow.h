#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimerEvent>

#include "tester.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent* e);

private slots:
    void on_comboBox_2_currentIndexChanged(const QString& arg1);
    void on_comboBox_currentIndexChanged(const QString& arg1);

private:
    Ui::MainWindow* ui;

    TESTER rele;
    void stest1(int i);
    void stest2(int i);

    void writeSettings();
    void readSettings();

    QSerialPort port;
    int timerId;
    // QObject interface
protected:
    void timerEvent(QTimerEvent* TimerEvent);
};

#endif // MAINWINDOW_H
