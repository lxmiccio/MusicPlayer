#include "Track.h"

Track::Track(QObject* parent) : QObject(parent)
{
}

Track::Track(const QVariantMap& tags, Album* album, QObject* parent) : QObject(parent)
{
    m_track = tags["track"].toUInt();
    m_title = tags["title"].toString();
    m_lyrics = tags["lyrics"].toString();
    m_year = tags["year"].toUInt();
    m_duration = tags["duration"].toUInt();
    m_path = tags["path"].toString();

    m_album = album;
    QObject::connect(album, SIGNAL(albumUpdated(Album*, quint8)), this, SIGNAL(albumUpdated(Album*, quint8)));
    QObject::connect(album, SIGNAL(artistUpdated(Artist*, quint8)), this, SIGNAL(artistUpdated(Artist*, quint8)));
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

quint16 Track::track() const
{
    return m_track;
}

void Track::setTrack(quint8 track)
{
    m_track = track;
    emit trackUpdated(this, Track::TRACK);
}

const QString& Track::title() const
{
    return m_title;
}

void Track::setTitle(const QString& title)
{
    if(title.length() > 0)
    {
        m_title = title;
        emit trackUpdated(this, Track::TITLE);
    }
}

const QString& Track::lyrics() const
{
    return m_lyrics;
}

void Track::setLyrics(const QString& lyrics)
{
    /* TODO: Change tag if .mp3, create .lrc file if .flac */
    m_lyrics = lyrics;
}

const QString& Track::readLyrics(bool force)
{
    static bool neverTried = true;

    if(m_lyrics.length() == 0 && (neverTried || force))
    {
        QVariantMap tag;

        if(m_path.endsWith(".mp3"))
        {
            TagUtils::readMp3Lyrics(QFileInfo(m_path), &tag);
        }

        if(tag.value("lyrics", "").toString().length() > 0)
        {
            m_lyrics = tag.value("lyrics", "").toString();
            emit trackUpdated(this, Track::LYRICS);
        }

        neverTried = false;
    }

    return m_lyrics;
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
    if(album)
    {
        m_album = album;
        emit albumChanged(album);
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
