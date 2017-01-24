#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <QFileInfo>
#include <QObject>
#include <QThread>

#include "TagUtils.h"
#include "Track.h"

class LoaderThread : public QObject
{
        Q_OBJECT
        QThread workerThread;

    public slots:
        void loadFile(const QFileInfo& file);

    signals:
        void fileLoaded(const Track& file);
};

#endif // LOADERTHREAD_H
