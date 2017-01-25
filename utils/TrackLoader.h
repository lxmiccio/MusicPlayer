#ifndef TRACKLOADER_H
#define TRACKLOADER_H

#include <QObject>
#include <QThread>
#include <QVector>

#include "LoaderThread.h"
#include "Track.h"

class TrackLoader : public QObject
{
        Q_OBJECT

    public:
        TrackLoader();
        void loadTracks(QList<QUrl> urls);
        static Track* load(QFileInfo& file);

    private slots:
        void onTrackLoaded(Track* track);
        void onTracksLoaded();

    signals:
        void trackLoaded(Track* track);

    private:
        QVector<LoaderThread*> m_trackLoaderThreads;
        QVector<QThread*> m_threads;
};

#endif // TRACKLOADER_H
