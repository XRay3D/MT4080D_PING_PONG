#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rele(this)
{
    ui->setupUi(this);
    connect(&rele, &TESTER::ReadyReadSignal, ui->lineEdit, &QLineEdit::setText);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{
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
