#ifndef TRACKLOADER_H
#define TRACKLOADER_H

#include <QFileInfo>
#include <QObject>
#include <QThread>
#include <QVector>

#include "TrackLoaderThread.h"
#include "Track.h"

class TrackLoader : public QObject
{
        Q_OBJECT

    public:
        TrackLoader();
        ~TrackLoader();

    public slots:
        void readTags(const QVector<QFileInfo>& files);

    signals:
        void tagsRead(Mp3Tags* tags);

    private slots:
        void onThreadFinished();

    private:
        QVector<TrackLoaderThread*> m_trackLoaderThreads;
        QVector<QThread*> m_threads;
};

#endif// TRACKLOADER_H
