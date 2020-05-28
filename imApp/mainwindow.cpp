#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtCore/QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_workerThread = new WorkerThread(this);

    auto list = this->_workerThread->getProcessModes();
    qDebug() << "list: " << list;
    ui->cb_ProcMode->addItems(list);

    connect(ui->pb_StartStop, &QPushButton::clicked,
            this->_workerThread,
            &WorkerThread::processStartStop);
    connect(ui->cb_ProcMode, &QComboBox::currentTextChanged,
            this->_workerThread,
            &WorkerThread::setProcessMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

