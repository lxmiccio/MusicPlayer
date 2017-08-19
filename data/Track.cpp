#include "Track.h"

#include "HttpRequestInput.h"
#include "LameWrapper.h"
#include "MusicLibrary.h"
#include "SoundTouchWrapper.h"
#include "Settings.h"

Track::Track(QObject* parent) : QObject(parent)
{
}

Track::Track(const QString& path, QObject* parent) : QObject(parent)
{
    m_tags.path = path;

    QObject::connect(this, SIGNAL(loadTrack()), this, SLOT(onLoadTrack()));
    QObject::connect(this, SIGNAL(changeTempo(qint16)), this, SLOT(onChangeTempo(qint16)));
    QObject::connect(this, SIGNAL(tempoChanged(QString)), MusicLibrary::instance(), SLOT(onTempoChanged(QString)));
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

void Track::modifyTempo(qint16 tempo, bool asynchronous)
{
    emit changeTempo(tempo);
    //    if(asynchronous)
    //    {
    //        emit changeTempo(tempo);
    //    }
    //    else
    //    {
    //        onChangeTempo(tempo);
    //    }
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

        TagLibWrapper::setMp3Tags(m_tags.path, m_tags);
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
    QString title = m_tags.title;
    if(title.contains("(Feat", Qt::CaseInsensitive))
    {
        title = title.left(title.indexOf("(Feat", 0, Qt::CaseInsensitive) - 1);
        title = title.left(title.indexOf("(Feat", 0, Qt::CaseInsensitive) - 1);
    }

    HttpRequestInput input("http://api.musixmatch.com/ws/1.1/track.search", "GET");
    input.addParameter("apikey", Settings::apiKeyMusixMatch());
    input.addParameter("q_artist", m_album->artist()->name());
    input.addParameter("q_track", title);

    HttpRequestWorker* worker = new HttpRequestWorker();
    QObject::connect(worker, SIGNAL(requestFinished(HttpRequestWorker*)), this, SLOT(onLyricsUrlFound(HttpRequestWorker*)));
    worker->execute(input);
}

void Track::downloadLyrics(const QString& title)
{
    HttpRequestInput input("http://api.musixmatch.com/ws/1.1/track.search", "GET");
    input.addParameter("apikey", Settings::apiKeyMusixMatch());
    input.addParameter("q_artist", m_album->artist()->name());
    input.addParameter("q_track", title);

    HttpRequestWorker* worker = new HttpRequestWorker();
    QObject::connect(worker, SIGNAL(requestFinished(HttpRequestWorker*)), this, SLOT(onLyricsUrlFound(HttpRequestWorker*)));
    worker->execute(input);
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

void Track::onChangeTempo(qint16 tempo)
{
    qDebug() << "changing tempo of " << m_tags.title;
    QString lameDecodeOutput = toWav();
    QString soundTouchOutput = modifyTempo(lameDecodeOutput, tempo);
    QString lameEncodeOutput = toMp3(soundTouchOutput);

    //    QFile(lameDecodeOutput).remove();
    //    QFile(soundTouchOutput).remove();

    Mp3Tags tags = m_tags;
    tags.title = QString(tags.title + " (x" + QString::number(tempo) + ")");

    TagLibWrapper::setMp3Tags(lameEncodeOutput, tags);
    TagLibWrapper::setMp3Cover(lameEncodeOutput, m_album->cover());
    TagLibWrapper::readMp3Cover(QFileInfo(lameEncodeOutput));

    emit tempoChanged(lameEncodeOutput);
}

void Track::onLyricsUrlFound(HttpRequestWorker* worker)
{
    if(!worker->isError())
    {
        QString url = worker->lyricsUrl();

        if(!url.isEmpty())
        {
            HttpRequestInput input(url);

            HttpRequestWorker* newWorker = new HttpRequestWorker();
            QObject::connect(newWorker, SIGNAL(requestFinished(HttpRequestWorker*)), this, SLOT(onLyricsDownloaded(HttpRequestWorker*)));
            newWorker->execute(input);
        }
        else
        {
            QString newLyrics = worker->input().parameter("q_track");
            if(newLyrics.length() >= 3)
            {
                downloadLyrics(newLyrics.left(newLyrics.length() - 2));
            }
        }
    }
    else
    {
        qDebug() << "Http request failed with error" << worker->errorMessage();
    }

    worker->deleteLater();
}

void Track::onLyricsDownloaded(HttpRequestWorker* worker)
{
    if(!worker->isError())
    {
        QRegExp rx("<p([^>]*)content([^>]*)>(.*)</p>");
        rx.setMinimal(true);

        QStringList lyrics;
        int index = 0;

        while((index = rx.indexIn(worker->response(), index)) != -1)
        {
            lyrics << rx.cap(3);
            index += rx.matchedLength();
        }

        if(lyrics.size() > 0)
        {
            m_tags.lyrics = lyrics.join("\n");

            /* Remove title and artist if lyrics starts with them */
            if(m_tags.lyrics.contains("\n") && (m_tags.lyrics.left(m_tags.lyrics.indexOf("\n")).contains(m_tags.title) && m_tags.lyrics.left(m_tags.lyrics.indexOf("\n")).contains(artist()->name())))
            {
                m_tags.lyrics = m_tags.lyrics.mid(m_tags.lyrics.indexOf("\n") + 1);
            }

            TagLibWrapper::setMp3Lyrics(m_tags.path, m_tags.lyrics);

            qDebug() << "Lyrics for track" << m_tags.title << "is" << m_tags.lyrics;
        }
        else
        {
            qDebug() << "Lyrics is empty";
        }
    }
    else
    {
        qDebug() << "Http request failed with error" << worker->errorMessage();
    }

    worker->deleteLater();
}

QString Track::toWav()
{
    QString lameDecodeOutput = QString(m_tags.path).replace(".mp3", ".wav");

    LameWrapper decoder(m_tags.path, lameDecodeOutput);
    decoder.decode();

    return lameDecodeOutput;
}

QString Track::modifyTempo(QString lameDecodeOutput, qint16 tempo)
{
    QString soundTouchOutput = QString(lameDecodeOutput).replace(".wav", " (x" + QString(QString::number(tempo) + ").wav"));

    SoundTouchWrapper soundTouch(lameDecodeOutput, soundTouchOutput);
    soundTouch.setTempo(tempo);
    soundTouch.process();

    return soundTouchOutput;
}

QString Track::toMp3(QString soundTouchOutput)
{
    QString lameEncodeOutput = QString(soundTouchOutput).replace(".wav", ".mp3");

    LameWrapper encoder(soundTouchOutput, lameEncodeOutput);
    encoder.encode();

    return lameEncodeOutput;
}

bool operator==(const Track& track1, const Track& track2)
{
    return track1.title() == track2.title();
}

bool operator<(const Track& track1, const Track& track2)
{
    return track1.title() < track2.title();
}
