#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
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

private:
    Ui::MainWindow* ui;

    TESTER rele;
    void stest1(int i);
    void stest2(int i);
};

#endif // MAINWINDOW_H
