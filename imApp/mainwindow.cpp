#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtCore/QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pb_DefineImgFolder, &QPushButton::clicked, this,
            &MainWindow::initOpenFileDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::configureWorkerThreadControls -
 *                      configures worker thread controls
 * @param wtr - WorkerThread instance
 */
void MainWindow::configureWorkerThreadControls(WorkerThread &p_wtr) {
    auto list = p_wtr.getProcessModes();
    this->ui->cb_ProcMode->addItems(list);
    qDebug() << "list: " << list;

    connect(this->ui->pb_StartStop, &QPushButton::clicked,
            &p_wtr, &WorkerThread::processStartStop);
    connect(this->ui->cb_ProcMode, &QComboBox::currentTextChanged,
            &p_wtr, &WorkerThread::setProcessMode);
}

/**
 * @brief MainWindow::initOpenFileDialog - initialize open file dialog
 */
void MainWindow::initOpenFileDialog() {
    qDebug() << "initOpenFileDialog: begin";

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                    QDir::currentPath(),
                                                    tr("Image Files (*.jpg *.tiff *.bmp)"));
}

