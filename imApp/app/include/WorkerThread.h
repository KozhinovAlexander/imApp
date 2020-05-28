/**
 * Simple image app worker thread definition
 * 
 * This thread runs stte machine for opening, processing and
 * displaying of an image.
 * 
 * Copyright: Alexander Kozhinov
 *              AlexanderKozhinov@yandex.com
 */

#ifndef WORKER_THREAD_H__
#define WORKER_THREAD_H__

#include <QObject>
#include <QThread>
#include <QImage>
#include <QMutex>

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QObject *parent = nullptr);
    ~WorkerThread();

    void processImage(const QImage &image);

signals:
    // void sendBlock(const Block &block);

public slots:
    void stopProcess();

protected:
    void run();

private:
    bool _abort;
    QImage _image;  // current loaded image to process and display
    QMutex _mutex;  // mutex for image memory protection
};

#endif  // WORKER_THREAD_H__
