/**
 * Simple image app worker thread implementation
 *
 * Copyright: Alexander Kozhinov
 *              AlexanderKozhinov@yandex.com
 */

#include <QtCore/QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QImageReader>

#include "WorkerThread.h"

WorkerThread::WorkerThread(QObject *parent) {
    Q_UNUSED(parent);

    this->_isStopped = true;  // processing is stopped at the beginning
    this->_currentProcMode = PROCESS_MODE_NONE;

    this->_procModeMap = std::map<QString, ProcessMode>();
    this->_procModeMap.insert(std::pair<QString,ProcessMode>("None",PROCESS_MODE_NONE));
    this->_procModeMap.insert(std::pair<QString,ProcessMode>("Horizontal",PROCESS_MODE_HORIZONTAL));
    this->_procModeMap.insert(std::pair<QString,ProcessMode>("Vertical",PROCESS_MODE_VERTICAL));

    this->_currPath = QString("");
    this->_nextPath = QString("");

    this->_currImgIdx = 0;
}

WorkerThread::~WorkerThread() {
}

/**
 * @brief WorkerThread::getProcessModes - provides list of process modes
 * @return QStringList - the list of processing modes
 */
QStringList WorkerThread::getProcessModes() {
    auto procModesList = QStringList();

    for( auto const& p : this->_procModeMap ) {
        Q_UNUSED(p);
        procModesList.append("");
    }

    for( auto const& p : this->_procModeMap ) {
        procModesList[p.second] = p.first;
    }

    return procModesList;
}

/**
 * @brief WorkerThread::setImgDir - sets new image directory
 */
void WorkerThread::setImgDir() {
    auto fileDialog = qobject_cast<QFileDialog*>(sender());
    Q_ASSERT(fileDialog);

    this->_nextPath = fileDialog->directory().path();

    qDebug() << "setImgDir: " << fileDialog->directory();
    qDebug() << "setImgDir: path:" << this->_nextPath;
}

/**
 * @brief WorkerThread::getSleepTime - thread sleep time getter
 * @return unisgned int - current thread sleep time
 */
unsigned int WorkerThread::getSleepTime() {
    return this->_SleepTime_ms;
}

/**
 * @brief WorkerThread::setSleepTime - thread sleep time setter
 * @param newSleepTime - new sleep time in ms
 */
void WorkerThread::setSleepTime(const unsigned int newSleepTime_ms) {
    this->_SleepTime_ms = newSleepTime_ms;
}

/**
 * @brief WorkerThread::getImage - provides image
 * @return QImage - an image
 */
QImage WorkerThread::getImage() {
    return this->_image.copy();
}

void WorkerThread::processStartStop() {
    auto button = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(button);

    if (this->_isStopped) {
        // Process stopped - run it again!
        qDebug() << "processStartStop: running";
        button->setDown(true);
        // this->start();
    } else {
        // Process running - stop int!
        qDebug() << "processStartStop: stopped";
        button->setDown(false);
        // this->quit();
    }

    this->_isStopped = !this->_isStopped;
}

void WorkerThread::setProcessMode() {
    auto comboBox = qobject_cast<QComboBox*>(sender());
    Q_ASSERT(comboBox);

    qDebug() << "processMode: choosen:" << comboBox->currentText();

    auto text = comboBox->currentText();
    auto it = this->_procModeMap.find(text);
    if ( it != this->_procModeMap.end() ) {
        this->_currentProcMode = this->_procModeMap.at(text);
    }

    qDebug() << "processMode: choosen:" << this->_currentProcMode;
}

void WorkerThread::run() {
    for(;;) {
        if(!this->_isStopped) {
            qDebug() << "WorkerThread: running...";

            // Load image (@TODO):
            this->_loadImage();

            // Process image (@TODO):
            this->_processImage();

            // Display image (@TODO):
            this->_displayImage();
        } else {
            qDebug() << "WorkerThread: stopped...";
        }

        this->msleep(this->_SleepTime_ms);
    }
}

/**
 * @brief WorkerThread::_loadImage - load new image
 */
void WorkerThread::_loadImage() {

    // Get list of images in path:
    if (this->_currPath.size()) {
        QDir dir(this->_nextPath);
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        dir.setSorting(QDir::Size | QDir::Reversed);
        dir.setNameFilters(QStringList()<<"*.jpg" << "*.bmp" << "*.tiff");

        QFileInfoList list = dir.entryInfoList();

        // Load image:
        qDebug() << "this->_currImgIdx: " << this->_currImgIdx;
        qDebug() << "list.size(): " << list.size();

        if ( this->_currImgIdx < static_cast<unsigned int>(list.size()) ) {
            QString imgName = this->_nextPath + "/" + list.at(this->_currImgIdx).fileName();
            qDebug() << "_loadImage: loading image: " << imgName;
            QImageReader reader(imgName);
            this->_image = reader.read();
            qDebug() << "_loadImage: loaded image size: " << this->_image.size();
        }

        // Update images index:
        this->_currImgIdx++;

        if ( this->_currImgIdx >= static_cast<unsigned int>(list.size())) {
            // Start from beginning:
            this->_currImgIdx = 0;
        }
    }

    // Update path:
    this->_currPath = this->_nextPath;
}

/**
 * @brief WorkerThread::_displayImage - display processed image
 */
void WorkerThread::_displayImage() {
    if (!this->_image.isNull()) {
        emit this->sendImage();
    }
}

/**
 * @brief WorkerThread::_processImage - processes current image
 */
void WorkerThread::_processImage() {

    switch(this->_currentProcMode) {
    case PROCESS_MODE_NONE:
        qDebug() << "processImage: PROCESS_MODE_NONE";
        break;
    case PROCESS_MODE_VERTICAL:
        qDebug() << "processImage: PROCESS_MODE_VERTICAL";
        this->_image = this->_image.mirrored(false, true);
        break;
    case PROCESS_MODE_HORIZONTAL:
        qDebug() << "processImage: PROCESS_MODE_HORIZONTAL";
        this->_image = this->_image.mirrored(true, false);
        break;
    default:
        qDebug() << "processImage: !!!unknown process mode!!!";
        Q_ASSERT(false);
        break;
    }
}
