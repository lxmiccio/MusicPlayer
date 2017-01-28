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
        static Track* load(QFileInfo& file);

    public slots:
        void loadTracks(const QVector<QFileInfo>& filesInfo);

    private slots:
        void onTrackLoaded(Track* track);
        void onTracksLoaded();

    signals:
        void trackLoaded(Track* track);

    private:
        QVector<TrackLoaderThread*> m_trackLoaderThreads;
        QVector<QThread*> m_threads;
};

#endif // TRACKLOADER_H
