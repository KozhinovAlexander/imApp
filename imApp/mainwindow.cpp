#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtCore/QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_dialog = new QFileDialog();

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
    connect(this->_dialog, &QFileDialog::currentChanged,
            &p_wtr, &WorkerThread::setImgDir);
    connect(&p_wtr, &WorkerThread::sendImage,
            this, &MainWindow::rcvDisplayImage);
}

/**
 * @brief MainWindow::rcvDisplayImage - recive and display the image
 *                                      from worker thread
 */
void MainWindow::rcvDisplayImage() {
    auto wrk = qobject_cast<WorkerThread*>(sender());
    Q_ASSERT(wrk);

    qDebug() << "rcvDisplayImage: triggered";

    QImage img = wrk->getImage();
    ui->lbl_Img->setPixmap(QPixmap::fromImage(img));
    ui->lbl_Img->setScaledContents( true );
    ui->lbl_Img->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

/**
 * @brief MainWindow::initOpenFileDialog - initialize open file dialog
 */
void MainWindow::initOpenFileDialog() {
    qDebug() << "initOpenFileDialog: begin";

    this->_dialog->setFileMode(QFileDialog::DirectoryOnly);
    this->_dialog->setOption(QFileDialog::ShowDirsOnly, false);
    this->_dialog->exec();

    qDebug() << "initOpenFileDialog: done";
}

