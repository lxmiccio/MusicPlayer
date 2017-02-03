
#include "Track.h"

#include <QFileInfo>

Track::Track()
{

}

Track::Track(const QVariantMap& tags, const Album* album)
{
    m_title = tags["title"].toString();
    m_lyrics = tags["lyrics"].toString();
    m_track = tags["track"].toUInt();
    m_year = tags["year"].toUInt();
    m_duration = tags["duration"].toUInt();
    m_path = tags["path"].toString();

    c_album = album;
}

const QString& Track::title() const
{
    return m_title;
}

void Track::setTitle(const QString& title)
{
    m_title = title;
}

const QString& Track::lyrics() const
{
    return m_lyrics;
}

void Track::setLyrics(const QString& lyrics)
{
    m_lyrics = lyrics;
}

quint16 Track::track() const
{
    return m_track;
}

void Track::setTrack(quint8 track)
{
    m_track = track;
}

quint16 Track::year() const
{
    return m_year;
}

void Track::setYear(quint8 year)
{
    m_year = year;
}

quint32 Track::duration() const
{
    return m_duration;
}

void Track::setDuration(quint32 duration)
{
    m_duration = duration;
}

const QString& Track::path() const
{
    return m_path;
}

void Track::setPath(const QString& path)
{
    m_path = path;
}

const Album* Track::album() const
{
    return c_album;
}

void Track::setAlbum(Album& album)
{
    c_album = &album;
}

const Artist* Track::artist() const
{
    return c_album ? c_album->artist() : NULL;
}

bool operator==(const Track& track1, const Track& track2)
{
    return track1.title() == track2.title();
}

bool operator<(const Track& track1, const Track& track2)
{
    return track1.title() < track2.title();
}
