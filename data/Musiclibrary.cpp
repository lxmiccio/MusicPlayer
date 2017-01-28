#include "MusicLibrary.h"

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

const QVector<Album*>& MusicLibrary::albums() const
{
    QVector<Album*> albums;

    foreach(Artist* i_artist, m_artists)
    {
        foreach(Album* i_album, i_artist->albums())
        {
            albums.push_back(i_album);
        }
    }

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

const QVector<Track*>& MusicLibrary::tracks() const
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
    Artist* artist = NULL;
    Album* album = NULL;
    Track* track = NULL;

    if(tags["artist"].toString().length() > 0 && tags["album"].toString().length() > 0 && tags["title"].toString().length() > 0 && tags["track"] > 0)
    {
        foreach(Artist* i_artist, m_artists)
        {
            if(i_artist->name() == tags["artist"].toString())
            {
                artist = i_artist;
                break;
            }
        }

        if(artist != NULL)
        {
            foreach(Album* i_album, artist->albums())
            {
                if(i_album->title() == tags["album"].toString())
                {
                    album = i_album;
                    break;
                }
            }

            if(album != NULL)
            {
                track = new Track(tags, album);
                album->addTrack(*track);

                emit trackAdded(track);
            }
            else
            {
                album = new Album(tags["album"].toString(), artist);
                artist->addAlbum(*album);

                track = new Track(tags, album);
                album->addTrack(*track);
                album->setCover(track->cover());

                emit albumAdded(album);
                emit trackAdded(track);
            }
        }
        else
        {
            artist = new Artist(tags["artist"].toString());
            m_artists.push_back(artist);

            album = new Album(tags["album"].toString(), artist);
            artist->addAlbum(*album);

            track = new Track(tags, album);
            album->addTrack(*track);
            album->setCover(track->cover());

            emit artistAdded(artist);
            emit albumAdded(album);
            emit trackAdded(track);
        }
    }

    return track;
}
