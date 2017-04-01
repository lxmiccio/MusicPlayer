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

    private slots:
        void onThreadFinished();

    signals:
        void tagsRead(QVariantMap* tags);

    private:
        QVector<TrackLoaderThread*> m_trackLoaderThreads;
        QVector<QThread*> m_threads;
};

#endif // TRACKLOADER_H
