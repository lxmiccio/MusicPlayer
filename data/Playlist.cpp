#include "Playlist.h"

Playlist::Playlist() : m_startingIndex(0)
{
}

Playlist* Playlist::fromAlbum(const Album* album, const Track* startingTrack)
{
    Playlist* playlist = new Playlist();

    if(album)
    {
        foreach(Track* i_track, album->tracks())
        {
            playlist->addTrack(*i_track);
        }

        if(startingTrack && (album->tracks().indexOf(const_cast<Track*>(startingTrack)) >= 0))
        {
            playlist->setStartingIndex(album->tracks().indexOf(const_cast<Track*>(startingTrack)));
        }
    }

    return playlist;
}

Playlist* Playlist::fromTracks(const QVector<const Track*> tracks, const Track* startingTrack)
{
    Playlist* playlist = new Playlist();

    foreach(const Track* i_track, tracks)
    {
        if(i_track)
        {
            playlist->addTrack(*i_track);
        }
    }

    if(startingTrack && (tracks.indexOf(startingTrack) >= 0))
    {
        playlist->setStartingIndex(tracks.indexOf(startingTrack));
    }

    return playlist;
}

const QVector<const Track*>& Playlist::tracks() const
{
    return c_tracks;
}

void Playlist::addTrack(const Track& track)
{
    c_tracks.push_back(&track);
}

void Playlist::removeTrack(const Track& track)
{
    c_tracks.removeOne(&track);
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
    c_tracks.clear();
    m_startingIndex = 0;
}
