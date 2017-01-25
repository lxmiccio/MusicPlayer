#include "LoaderThread.h"
#include <QDebug>
static Track* loadTrack(QFileInfo &file)
{
    Track* track = new Track();

    if(file.suffix() == "flac")
    {
        track = TagUtils::readFlac(file);
    }
    else if(file.suffix() == "mp3")
    {
        track = TagUtils::readMp3(file);
    }

    return track;
}

void LoaderThread::loadTracks(const QList<QUrl>& tracks)
{
    QListIterator<QUrl> iterator(tracks);

    while(iterator.hasNext())
    {
        QFileInfo fileInfo = iterator.next().toLocalFile();

        if(fileInfo.suffix() == "flac" || fileInfo.suffix() == "mp3")
            m_tracks.append(iterator.next().toLocalFile());
    }

    m_future = QtConcurrent::mapped(m_tracks.begin(), m_tracks.end(), loadTrack);

    QObject::connect(&m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(onTrackLoaded(int)));
    QObject::connect(&m_futureWatcher, SIGNAL(finished()), this, SLOT(onTracksLoaded()));

    m_futureWatcher.setFuture(m_future);
}

void LoaderThread::onTrackLoaded(int index)
{
    emit trackLoaded(m_future.resultAt(index));
}

void LoaderThread::onTracksLoaded()
{
    emit tracksLoaded();
}
