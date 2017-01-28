#include "Playlist.h"

Playlist::Playlist()
{
    c_tracks = QVector<const Track*>();
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

void Playlist::clear()
{
    c_tracks.clear();
}
