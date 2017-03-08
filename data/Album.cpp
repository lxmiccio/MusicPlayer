#include "Album.h"

Album::Album(QObject* parent) : QObject(parent)
{
}

Album::Album(const QString& title, Artist* artist, QObject* parent) : QObject(parent)
{
    m_artist = artist;
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
    foreach(Track* i_track, m_tracks) {
        if(i_track->title() == title) {
            return i_track;
        }
    }

    return NULL;
}

void Album::addTrack(Track* track)
{
    if(track) {
        m_tracks.push_back(track);
        std::sort(m_tracks.begin(), m_tracks.end());
    }
}

bool Album::removeTrack(Track* track)
{
    return m_tracks.removeOne(track);
}

bool Album::removeTrack(const QString& title)
{
    foreach(Track* i_track, m_tracks) {
        if(i_track->title() == title) {
            return m_tracks.removeOne(i_track);
        }
    }

    return false;
}

Artist* Album::artist() const
{
    return m_artist;
}

void Album::setArtist(Artist* artist)
{
    if(artist) {
        m_artist = artist;
    }
}

bool operator==(const Album& album1, const Album& album2)
{
    return album1.title() == album2.title();
}

bool operator<(const Album& album1, const Album& album2)
{
    return album1.title() < album2.title();
}
