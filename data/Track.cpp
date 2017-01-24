
#include "Track.h"

#include <QFileInfo>

Track::Track()
{

}

Track::Track(const QVariantMap& tags, const Album* album)
{
    m_title = tags["title"].toString();
    m_cover = tags["cover"].value<QPixmap>();
    m_lyrics = tags["lyrics"].toString();
    m_track = tags["track"].toUInt();
    m_year = tags["year"].toUInt();
    m_duration = tags["duration"].toUInt();
    m_bitrate = tags["bitrate"].toUInt();
    m_path = tags["path"].toString();
    m_size = tags["size"].toULongLong();

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

const QPixmap& Track::cover() const
{
    return m_cover;
}

void Track::setCover(const QPixmap &cover)
{
    m_cover = cover;
}

const QString& Track::lyrics() const
{
    return m_lyrics;
}

void Track::setLyrics(const QString& lyrics)
{
    m_lyrics = lyrics;
}

quint8 Track::track() const
{
    return m_track;
}

void Track::setTrack(quint8 track)
{
    m_track = track;
}

quint8 Track::year() const
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

QString Track::durationInMinutes() const
{
    return QString("%1:%2").arg(m_duration / 60, 2, 10, QChar('0')).arg(m_duration % 60, 2, 10, QChar('0'));
}

void Track::setDuration(quint32 duration)
{
    m_duration = duration;
}

quint32 Track::bitrate() const
{
    return m_bitrate;
}

void Track::setBitrate(quint32 bitrate)
{
    m_bitrate = bitrate;
}

const QString& Track::path() const
{
    return m_path;
}

void Track::setPath(const QString &path)
{
    m_path = path;
}

quint64 Track::size() const
{
    return m_size;
}

void Track::setSize(quint64 size)
{
    m_size = size;
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
    return c_album->artist();
}

bool Track::isSupportedSuffix(const QString& suffix)
{
    static QVector<QString> suffixes;

    if(suffixes.isEmpty())
    {
        suffixes.append("flac");
        suffixes.append("mp3");
    }

    return suffixes.indexOf(suffix) == -1 ? false : true;
}

bool operator==(const Track& track1, const Track& track2)
{
    return track1.title() == track2.title();
}

bool operator<(const Track& track1, const Track& track2)
{
    return track1.title() < track2.title();
}
