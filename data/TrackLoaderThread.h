#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <QtConcurrent>
#include <QFileInfo>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>
#include <QThread>

#include "TagUtils.h"
#include "Track.h"

class TrackLoaderThread : public QObject
{
        Q_OBJECT
        QThread thread;

    public slots:
        void loadTracks(const QVector<QFileInfo>& tracks);

    private slots:
        void onTrackLoaded(int index);
        void onTracksLoaded();

    signals:
        void trackLoaded(Track* tracks);
        void tracksLoaded();

    private:
        QVector<QFileInfo> m_tracks;
        QFuture<Track*> m_future;
        QFutureWatcher<Track*> m_futureWatcher;
};

#endif // LOADERTHREAD_H
