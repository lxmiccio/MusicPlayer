#include "MusicLibrary.h"

#include "TagUtils.h"

QPointer<MusicLibrary> MusicLibrary::m_instance = 0;

MusicLibrary::MusicLibrary()
{
}

MusicLibrary* MusicLibrary::instance()
{
    if(m_instance.isNull())
    {
        m_instance = new MusicLibrary();
    }

    return m_instance;
}

const QVector<Artist*>& MusicLibrary::artists() const
{
    return m_artists;
}

Artist* MusicLibrary::artist(const QString& name) const
{
    foreach(Artist* i_artist, m_artists)
    {
        if(i_artist->name() == name)
        {
            return i_artist;
        }
    }

    return NULL;
}

bool MusicLibrary::removeArtist(Artist& artist)
{
    return m_artists.removeOne(&artist);
}

bool MusicLibrary::removeArtist(const QString& name)
{
    return m_artists.removeOne(artist(name));
}

const QVector<Album*> MusicLibrary::albums() const
{
    QVector<Album*> albums;

    foreach(Artist* i_artist, m_artists)
    {
        foreach(Album* i_album, i_artist->albums())
        {
            albums.push_back(i_album);
        }
    }

    qSort(albums.begin(), albums.end(), [] (const Album* album1, const Album* album2) -> bool
    {
        if(album1->artist()->name() != album2->artist()->name())
        {
            return album1->artist()->name() < album2->artist()->name();
        }
        else
        {
            return album1->title() < album2->title();
        }
    });

    return albums;
}

Album* MusicLibrary::album(const QString& title) const
{
    foreach(Artist* i_artist, m_artists)
    {
        foreach(Album* i_album, i_artist->albums())
        {
            if(i_album->title() == title)
            {
                return i_album;
            }
        }
    }

    return NULL;
}

Album* MusicLibrary::album(const QString& title, const QString& artistName) const
{
    foreach(Artist* i_artist, m_artists)
    {
        if(i_artist->name() == artistName)
        {
            foreach(Album* i_album, i_artist->albums())
            {
                if(i_album->title() == title)
                {
                    return i_album;
                }
            }
        }
    }

    return NULL;
}

bool MusicLibrary::removeAlbum(Album& album)
{
    foreach(Artist* i_artist, m_artists)
    {
        if(i_artist->removeAlbum(album))
        {
            return true;
        }
    }

    return false;
}

bool MusicLibrary::removeAlbum(const QString& albumName, const QString& artistName)
{
    if(artist(artistName))
    {
        return artist(artistName)->removeAlbum(albumName);
    }
    else
    {
        return false;
    }
}

const QVector<Track*> MusicLibrary::tracks() const
{
    QVector<Track*> tracks;

    foreach(Artist* i_artist, m_artists)
    {
        foreach(Album* i_album, i_artist->albums())
        {
            foreach(Track *i_track, i_album->tracks())
            {
                tracks.push_back(i_track);
            }
        }
    }

    qSort(tracks.begin(), tracks.end(), [] (const Track* track1, const Track* track2) -> bool
    {
        if(track1->album()->artist()->name() != track2->album()->artist()->name())
        {
            return track1->album()->artist()->name() < track2->album()->artist()->name();
        }
        else if(track1->album()->title() != track2->album()->title())
        {
            return track1->album()->title() < track2->album()->title();
        }
        else
        {
            return track1->title() < track2->title();
        }
    });

    return tracks;
}

bool MusicLibrary::removeTrack(Track& track)
{
    foreach(Artist* i_artist, m_artists)
    {
        foreach(Album* i_album, i_artist->albums())
        {
            if(i_album->removeTrack(track))
            {
                return true;
            }
        }
    }

    return false;
}

bool MusicLibrary::removeTrack(const QString& trackTitle, const QString& albumTitle)
{
    if(album(albumTitle) != NULL)
    {
        return album(albumTitle)->removeTrack(trackTitle);
    }

    return false;
}

Track* MusicLibrary::addTrack(const QVariantMap& tags)
{
    QMutexLocker locker(&m_mutex);

    Artist* l_artist = NULL;
    Album* l_album = NULL;
    Track* l_track = NULL;

    if(tags["artist"].toString().length() > 0)
    {
        l_artist = artist(tags["artist"].toString());

        if(!l_artist)
        {
            l_artist = new Artist(tags["artist"].toString());
            m_artists.push_back(l_artist);
            emit artistAdded(l_artist);
        }
    }
    else
    {
        l_artist = artist("Unknown");

        if(!l_artist)
        {
            l_artist = new Artist("Unknown");
            m_artists.push_back(l_artist);
            emit artistAdded(l_artist);
        }
    }

    if(tags["album"].toString().length() > 0)
    {
        l_album = album(tags["album"].toString());

        if(!l_album)
        {
            l_album = new Album(tags["album"].toString(), l_artist);
            l_album->setCover(TagUtils::readMp3Cover(QFileInfo(tags["path"].toString())));
            l_artist->addAlbum(*l_album);
            emit albumAdded(l_album);
        }
    }
    else
    {
        l_album = album("Unknown", l_artist->name());

        if(!l_album)
        {
            l_album = new Album("Unknown", l_artist);
            l_artist->addAlbum(*l_album);
            emit albumAdded(l_album);
        }
    }

    if(tags["title"].toString().length() > 0)
    {
        // tags["title"] = tags["patch"].toString().split("/").back().at(0);
    }

    l_track = const_cast<Track*>(l_album->track(tags["title"].toString()));

    if(!l_track)
    {
        l_track = new Track(tags, l_album);
        l_album->addTrack(*l_track);
        emit trackAdded(l_track);
    }

    return l_track;
}
