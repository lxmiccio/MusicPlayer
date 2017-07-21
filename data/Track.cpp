#include "Track.h"

#include <QDebug>

Track::Track(QObject* parent) : QObject(parent)
{
}

Track::Track(const QString& path, QObject* parent) : QObject(parent)
{
    m_tags.path = path;

    QObject::connect(this, SIGNAL(loadTrack()), this, SLOT(onLoadTrack()));
}

void Track::load(bool asynchronous)
{
    if(asynchronous)
    {
        emit loadTrack();
    }
    else
    {
        onLoadTrack();
    }
}

Mp3Tags Track::mp3Tags() const
{
    return m_tags;
}

quint16 Track::track() const
{
    return m_tags.track;
}

void Track::setTrack(quint8 track)
{
    m_tags.track = track;
    emit trackUpdated(this, Track::TRACK);
}

const QString& Track::title() const
{
    return m_tags.title;
}

void Track::setTitle(const QString& title)
{
    if(title.length() > 0)
    {
        m_tags.title = title;
        emit trackUpdated(this, Track::TITLE);
    }
}

const QString& Track::lyrics() const
{
    return m_tags.lyrics;
}

void Track::setLyrics(const QString& lyrics)
{
    /* TODO: Change tag if.mp3, create .lrc file if.flac */
    m_tags.lyrics = lyrics;
}

const QString& Track::readLyrics(bool force)
{
    static bool neverTried = true;

    if(m_tags.lyrics.length() == 0 && (neverTried || force))
    {
        if(m_tags.path.endsWith(".mp3"))
        {
            TagLibWrapper::readMp3Lyrics(m_tags.path, &m_tags);
        }

        if(m_tags.lyrics.length() > 0)
        {
            emit trackUpdated(this, Track::LYRICS);
        }

        neverTried = false;
    }

    return m_tags.lyrics;
}

void Track::downloadLyrics()
{
    qDebug() << "Downloading lyrics for track" << m_tags.title;

    QString title = m_tags.title;
    if(title.contains("(Feat", Qt::CaseInsensitive))
    {
        title = title.left(title.indexOf("(Feat", 0, Qt::CaseInsensitive) - 1);
    }

    HttpRequestInput input("http://api.musixmatch.com/ws/1.1/track.search", "GET");
    input.addParameter("apikey", Settings::apiKey());
    input.addParameter("q_artist", m_album->artist()->name());
    input.addParameter("q_track", title);

    HttpRequestWorker* worker = new HttpRequestWorker();
    QObject::connect(worker, SIGNAL(on_execution_finished(HttpRequestWorker*)), this, SLOT(onLyricsUrlFound(HttpRequestWorker*)));
    worker->execute(&input);
}

quint32 Track::duration() const
{
    return m_tags.duration;
}

void Track::setDuration(quint32 duration)
{
    m_tags.duration = duration;
}

quint16 Track::year() const
{
    return m_tags.year;
}

void Track::setYear(quint8 year)
{
    m_tags.year = year;
}

QString Track::path() const
{
    return m_tags.path;
}

void Track::setPath(const QString& path)
{
    m_tags.path = path;
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
        QObject::connect(m_album, SIGNAL(albumUpdated(Album*, quint8)), this, SIGNAL(albumUpdated(Album*, quint8)));
        QObject::connect(m_album, SIGNAL(artistUpdated(Artist*, quint8)), this, SIGNAL(artistUpdated(Artist*, quint8)));

        emit albumChanged(album);
    }
}

Artist* Track::artist() const
{
    return m_album ? m_album->artist() : NULL;
}

void Track::onLoadTrack()
{
    if(m_tags.path.endsWith("flac"))
    {
        TagLibWrapper::readFlacTags(m_tags.path, &m_tags);
    }
    else if(m_tags.path.endsWith("mp3"))
    {
        TagLibWrapper::readMp3Tags(m_tags.path, &m_tags);
        TagLibWrapper::readMp3Lyrics(m_tags.path, &m_tags);
    }

    emit trackLoaded(this, m_tags.artist, m_tags.album);
}

void Track::onLyricsUrlFound(HttpRequestWorker* worker)
{
    QString url = worker->lyricsUrl();

    qDebug() << "Lyrics url for track" << m_tags.title << "is" << url;

    HttpRequestInput input(url);

    HttpRequestWorker* newWorker = new HttpRequestWorker();
    QObject::connect(newWorker, SIGNAL(on_execution_finished(HttpRequestWorker*)), this, SLOT(onLyricsDownloaded(HttpRequestWorker*)));
    newWorker->execute(&input);

    worker->deleteLater();
}

void Track::onLyricsDownloaded(HttpRequestWorker* worker)
{
    QRegExp rx("<p([^>]*)content([^>]*)>(.*)</p>");
    rx.setMinimal(true);

    QStringList lyrics;
    int index = 0;

    while((index = rx.indexIn(worker->m_response, index)) != -1)
    {
        lyrics << rx.cap(3);
        index += rx.matchedLength();
    }

    if(lyrics.size() > 0)
    {
        m_tags.lyrics = lyrics.join("\n");
        TagLibWrapper::setMp3Lyrics(m_tags.path, m_tags.lyrics);

        qDebug() << "Lyrics for track" << m_tags.title << "is" << m_tags.lyrics;
    }
    worker->deleteLater();
}

bool operator==(const Track& track1, const Track& track2)
{
    return track1.title() == track2.title();
}

bool operator<(const Track& track1, const Track& track2)
{
    return track1.title() < track2.title();
}
