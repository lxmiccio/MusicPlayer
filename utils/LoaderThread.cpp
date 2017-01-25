#include "LoaderThread.h"

static Track* loadTrack(QFileInfo &file)
{
    Track* track = new Track();

    track->setTitle(file.absoluteFilePath());
    /* TODO */

    return track;
}

void LoaderThread::loadTracks(const QList<QUrl>& tracks)
{
    QListIterator<QUrl> iterator(tracks);

    while(iterator.hasNext())
    {
        m_tracks.append(iterator.next().toLocalFile());
    }

    m_future = QtConcurrent::mapped(m_tracks.begin(), m_tracks.end(), loadTrack);
    m_futureWatcher.setFuture(m_future);

    QObject::connect(&m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(onTrackLoaded(int)));
    QObject::connect(&m_futureWatcher, SIGNAL(finished()), this, SLOT(onTracksLoaded()));
}

void LoaderThread::onTrackLoaded(int index)
{
    emit trackLoaded(m_future.resultAt(index));
}

void LoaderThread::onTracksLoaded()
{
    emit tracksLoaded();
}
