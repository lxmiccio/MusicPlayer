#include "Track.h"

#include <QFileInfo>

Track::Track(QObject* parent) : QObject(parent)
{

}

Track::Track(const QVariantMap& tags, Album* album, QObject* parent) : QObject(parent)
{
    m_title = tags["title"].toString();
    m_lyrics = tags["lyrics"].toString();
    m_track = tags["track"].toUInt();
    m_year = tags["year"].toUInt();
    m_duration = tags["duration"].toUInt();
    m_path = tags["path"].toString();

    m_album = album;
}

Track::Track(quint16 track, const QString& title, const QString& lyrics, quint16 year, quint32 duration, const QString& path, Album* album, QObject* parent) : QObject(parent)
{
    m_title = title;
    m_lyrics = lyrics;
    m_track = track;
    m_year = year;
    m_duration = duration;
    m_path = path;

    m_album = album;
}

const QString& Track::title() const
{
    return m_title;
}

void Track::setTitle(const QString& title)
{
    m_title = title;
}

quint16 Track::track() const
{
    return m_track;
}

void Track::setTrack(quint8 track)
{
    m_track = track;
}

quint32 Track::duration() const
{
    return m_duration;
}

void Track::setDuration(quint32 duration)
{
    m_duration = duration;
}

quint16 Track::year() const
{
    return m_year;
}

void Track::setYear(quint8 year)
{
    m_year = year;
}

const QString& Track::lyrics() const
{
    return m_lyrics;
}

void Track::setLyrics(const QString& lyrics)
{
    m_lyrics = lyrics;
}

const QString& Track::path() const
{
    return m_path;
}

void Track::setPath(const QString& path)
{
    m_path = path;
}

Album* Track::album() const
{
    return m_album;
}

void Track::setAlbum(Album* album)
{
    if(album) {
        m_album = album;
    }
}

Artist* Track::artist() const
{
    return m_album ? m_album->artist() : NULL;
}

bool operator==(const Track& track1, const Track& track2)
{
    return track1.title() == track2.title();
}

bool operator<(const Track& track1, const Track& track2)
{
    return track1.title() < track2.title();
}
