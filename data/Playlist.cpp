#include "Playlist.h"

#include "MusicLibrary.h"

Playlist::Playlist(const QString& name, QObject* parent) : QObject(parent)
{
    m_name = name;
    m_startingIndex = 0;
}

Playlist* Playlist::fromAlbum(Album* album, Track* startingTrack)
{
    Playlist* playlist = new Playlist("Playing");

    if(album)
    {
        foreach(Track* i_track, album->tracks())
        {
            playlist->addTrack(i_track);
        }

        if(startingTrack && (album->tracks().indexOf(startingTrack) >= 0))
        {
            playlist->setStartingIndex(album->tracks().indexOf(startingTrack));
        }
    }

    return playlist;
}

Playlist* Playlist::fromTracks(QVector<Track*> tracks, Track* startingTrack)
{
    Playlist* playlist = new Playlist("Playing");

    foreach(Track* i_track, tracks)
    {
        if(i_track)
        {
            playlist->addTrack(i_track);
        }
    }

    if(startingTrack && (tracks.indexOf(startingTrack) >= 0))
    {
        playlist->setStartingIndex(tracks.indexOf(startingTrack));
    }

    return playlist;
}

const QVector<Track*>& Playlist::tracks() const
{
    return m_tracks;
}

void Playlist::addTrack(const QString& path)
{
    if(!MusicLibrary::instance()->exists(path) && (path.endsWith("flac") || path.endsWith("mp3")))
    {
        Track* track = new Track(path);
        MusicLibrary::instance()->onTrackToLoad(track);

        m_tracks.push_back(track);
    }
    else
    {
        m_tracks.push_back(MusicLibrary::instance()->track(path));
    }
}

void Playlist::addTrack(Track* track)
{
    if(track)
    {
        m_tracks.push_back(track);
    }
}

void Playlist::removeTrack(Track* track)
{
    m_tracks.removeOne(track);
    emit playlistUpdated();
}

const QString& Playlist::name() const
{
    return m_name;
}

void Playlist::setName(const QString& name)
{
    m_name = name;
}

quint16 Playlist::startingIndex()
{
    return m_startingIndex;
}

void Playlist::setStartingIndex(quint16 startingIndex)
{
    m_startingIndex = startingIndex;
}

void Playlist::clear()
{
    m_tracks.clear();
    m_startingIndex = 0;
}
