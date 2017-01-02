#include "playlist.h"

Playlist::Playlist(const QString& name)
{
    m_name = name;

    c_tracks = QVector<const Track*>();
}

const QString& Playlist::name() const
{
    return m_name;
}

void Playlist::setName(const QString& name)
{
    m_name = name;
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

void Playlist::removeAllTracks()
{
    c_tracks.clear();
}
