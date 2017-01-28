#include "TrackLoaderThread.h"

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

void TrackLoaderThread::loadTracks(const QVector<QFileInfo>& tracks)
{
    for(QVector<QFileInfo>::ConstIterator i_track = tracks.begin(); i_track < tracks.end(); ++i_track)
    {
        if(i_track->suffix() == "flac" || i_track->suffix() == "mp3")
        {
            m_tracks.push_back(*i_track);
        }
    }

    QObject::connect(&m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(onTrackLoaded(int)));
    QObject::connect(&m_futureWatcher, SIGNAL(finished()), this, SLOT(onTracksLoaded()));

    m_future = QtConcurrent::mapped(m_tracks.begin(), m_tracks.end(), loadTrack);
    m_futureWatcher.setFuture(m_future);
}

void TrackLoaderThread::onTrackLoaded(int index)
{
    emit trackLoaded(m_future.resultAt(index));
}

void TrackLoaderThread::onTracksLoaded()
{
    emit tracksLoaded();
}
