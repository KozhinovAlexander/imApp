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

#include <QThread>
#include <QImage>
#include <QMutex>

/**
 * @brief The ProcessMode enum
 */
enum ProcessMode {
    PROCESS_MODE_NONE,
    PROCESS_MODE_HORIZONTAL,
    PROCESS_MODE_VERTICAL,
};

/**
 * @brief The WorkerThread class
 */
class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QObject *parent = nullptr);
    ~WorkerThread();

    void processImage(const QImage &image);
    QStringList getProcessModes();

// signals:
//     void sendBlock(const Block &block);

public slots:
    void processStartStop();
    void setProcessMode();

protected:
    void run();

private:
    bool _isStopped;
    ProcessMode _currentProcMode;
    std::map<QString, ProcessMode> _procModeMap;
    QImage _image;  // current loaded image to process and display
    QMutex _mutex;  // mutex for image memory protection
};

#endif  // WORKER_THREAD_H__
