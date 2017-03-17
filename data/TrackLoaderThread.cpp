#include "TrackLoaderThread.h"

#include "MusicLibrary.h"

static Track* loadTrack(QFileInfo &file)
{
    Track* track = new Track();

    if(file.suffix() == "flac")
    {
        track = TagUtils::readFlac(file);
    }
    else if(file.suffix() == "mp3")
    {
#if 1
        track = TagUtils::readMp3(file);
#else
        QVariantMap tags;
        tags["track"] = 1;
        tags["title"] = file.fileName();
        tags["path"] = file.canonicalFilePath();

        tags["album"] = "album";
        tags["artist"] = "artist";
        tags["duration"] = 300;

        MusicLibrary* musicLibrary = MusicLibrary::instance();
        return musicLibrary->addTrack(tags);
#endif
    }

    return track;
}

TrackLoaderThread::~TrackLoaderThread()
{
    m_future.cancel();
    m_futureWatcher.cancel();
    m_future.waitForFinished();
    m_futureWatcher.waitForFinished();
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
