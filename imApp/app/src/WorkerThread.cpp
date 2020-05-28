/**
 * Simple image app worker thread implementation
 *
 * Copyright: Alexander Kozhinov
 *              AlexanderKozhinov@yandex.com
 */

#include <QtCore/QDebug>

#include "WorkerThread.h"

/**
 * CTOR
 */
WorkerThread::WorkerThread(QObject *parent) {
    qDebug() << "Create WorkerThread from parent: " << parent;
}

/**
 * DTOR
 */
WorkerThread::~WorkerThread() {
}

void WorkerThread::run() {
    qDebug() << "Start WorkerThread";
}
