#include "Album.h"

Album::Album()
{
}

Album::Album(const QString& title, const Artist* artist)
{    
    c_artist = artist;

    m_title = title;
}

const QString& Album::title() const
{
    return m_title;
}

void Album::setTitle(const QString& title)
{
    m_title = title;
}

const QPixmap& Album::cover() const
{
    return m_cover;
}

void Album::setCover(const QPixmap& cover)
{
    m_cover = cover;
}

const QVector<Track*>& Album::tracks() const
{
    return m_tracks;
}

const Track* Album::track(const QString& title) const
{
    foreach(Track* i_track, m_tracks)
    {
        if(i_track->title() == title)
        {
            return i_track;
        }
    }

    return NULL;
}

void Album::addTrack(Track& track)
{
    m_tracks.push_back(&track);
    m_cover = track.cover();

    std::sort(m_tracks.begin(), m_tracks.end(), [] (const Track* track1, const Track* track2) -> bool {
        return track1->track() < track2->track();
    });
}

bool Album::removeTrack(Track& track)
{
    return m_tracks.removeOne(&track);
}

bool Album::removeTrack(const QString& title)
{
    foreach(Track* i_track, m_tracks)
    {
        if(i_track->title() == title)
        {
            return m_tracks.removeOne(i_track);
        }
    }

    return false;
}

const Artist* Album::artist() const
{
    return c_artist;
}

void Album::setArtist(const Artist& artist)
{
    c_artist = &artist;
}

bool operator==(const Album& album1, const Album& album2)
{
    return album1.title() == album2.title();
}
