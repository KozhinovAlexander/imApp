/**
 * Simple image app worker thread implementation
 *
 * Copyright: Alexander Kozhinov
 *              AlexanderKozhinov@yandex.com
 */

#include <QtCore/QDebug>

#include "WorkerThread.h"

WorkerThread::WorkerThread(QObject *parent) {
    Q_UNUSED(parent);
}

WorkerThread::~WorkerThread() {
}

void WorkerThread::processImage(const QImage &image) {
    Q_UNUSED(image);
}

void WorkerThread::stopProcess() {
}

void WorkerThread::run() {
}
