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

class LoaderThread : public QObject
{
        Q_OBJECT
        QThread thread;

    public slots:
        void loadTracks(const QList<QUrl>& tracks);

    private slots:
        void onTrackLoaded(int index);
        void onTracksLoaded();

    signals:
        void trackLoaded(Track* tracks);
        void tracksLoaded();

    private:
        QList<QFileInfo> m_tracks;
        QFuture<Track*> m_future;
        QFutureWatcher<Track*> m_futureWatcher;
};

#endif // LOADERTHREAD_H
