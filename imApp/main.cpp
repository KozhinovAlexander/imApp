#include "mainwindow.h"

#include <QApplication>
#include <QtCore/QDebug>

#include "WorkerThread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    WorkerThread *workTrd = new WorkerThread(&w);

    w.configureWorkerThreadControls(*workTrd);

    w.show();
    workTrd->start();

    return a.exec();
}
