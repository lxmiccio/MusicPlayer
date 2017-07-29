#include "Album.h"

#include "GuiUtils.h"

Album::Album(QObject* parent) : QObject(parent)
{
}

Album::Album(const QString& title, Artist* artist, QObject* parent) : QObject(parent)
{
    m_title = title;

    m_artist = artist;
    QObject::connect(artist, SIGNAL(artistUpdated(Artist*, quint8)), this, SLOT(onArtistUpdated(Artist*,quint8)));
}

const QString& Album::title() const
{
    return m_title;
}

void Album::setTitle(const QString& title)
{
    m_title = title;
    emit albumUpdated(this, Album::TITLE);
}

const QPixmap& Album::cover() const
{
    return m_cover;
}

void Album::setCover(const QPixmap& cover)
{
    m_cover = cover;
    emit albumUpdated(this, Album::COVER);
}

const QVector<Track*>& Album::tracks() const
{
    return m_tracks;
}

Track* Album::track(const QString& title) const
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

void Album::addTrack(Track* track)
{
    if(track)
    {
        QObject::connect(track, SIGNAL(trackUpdated(Track*, quint8)), this, SIGNAL(trackUpdated(Track*, quint8)));
        m_tracks.push_back(track);

        sort();
        emit trackAdded(track);
    }
}

bool Album::removeTrack(Track* track)
{
    if(m_tracks.removeOne(track))
    {
        emit trackRemoved(track);

        track->deleteLater();
        track = NULL;

        if(m_tracks.isEmpty())
        {
            m_artist->removeAlbum(this);
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool Album::removeTrack(const QString& title)
{
    foreach(Track* i_track, m_tracks)
    {
        if(i_track->title() == title)
        {
            return removeTrack(i_track);
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
    if(artist)
    {
        m_artist = artist;
        emit artistChanged(artist);
    }
}

void Album::sort()
{
    std::sort(m_tracks.begin(), m_tracks.end(), [] (const Track* track1, const Track* track2) -> bool
    {
        return track1->track() < track2->track();
    });
}

void Album::onArtistUpdated(Artist* artist, quint8 fields)
{
    Q_UNUSED(fields);

    if(artist && artist == this->artist())
    {
        emit albumUpdated(this, Album::ARTIST);
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
