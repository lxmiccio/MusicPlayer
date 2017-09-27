#include "MusicLibrary.h"

#include "TagLibWrapper.h"

MusicLibrary* MusicLibrary::m_instance = 0;

MusicLibrary::MusicLibrary()
{
}

MusicLibrary* MusicLibrary::instance()
{
    if(!m_instance)
    {
        m_instance = new MusicLibrary();
    }

    return m_instance;
}

void MusicLibrary::deleteInstance()
{
    if(m_instance)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

const QVector<Artist*>& MusicLibrary::artists() const
{
    return m_artists;
}

Artist* MusicLibrary::artist(const QString& name) const
{
    foreach(Artist* i_artist, m_artists)
    {
        if(i_artist && i_artist->name() == name)
        {
            return i_artist;
        }
    }

    return NULL;
}

bool MusicLibrary::removeArtist(Artist* artist)
{
    delete artist;
    return m_artists.removeOne(artist);
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

bool MusicLibrary::removeAlbum(Album* album)
{
    if(album && album->artist())
    {
        return album->artist()->removeAlbum(album);
    }
    else
    {
        return false;
    }
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

    return tracks;
}

bool MusicLibrary::removeTrack(Track* track)
{
    if(track && track->album())
    {
        return track->album()->removeTrack(track);
    }
    else
    {
        return false;
    }
}

bool MusicLibrary::removeTrack(const QString& trackTitle, const QString& albumTitle)
{
    if(album(albumTitle))
    {
        return album(albumTitle)->removeTrack(trackTitle);
    }
    else
    {
        return false;
    }
}

void MusicLibrary::onTrackLoaded(Track* p_track, QString p_artist, QString p_album)
{
    if(p_track)
    {
        QMutexLocker locker(&m_mutex);

        Artist* l_artist = NULL;
        Album* l_album = NULL;

        if(p_track->duration() > 0)
        {
            QString l_path = p_track->path();
            QString l_trackTitle = p_track->title();

            l_artist = artist(p_artist);
            if(!l_artist)
            {
                l_artist = new Artist(p_artist);
                QObject::connect(l_artist, SIGNAL(artistRemoved(Artist*)), this, SLOT(onArtistRemoved(Artist*)));
                m_artists.push_back(l_artist);
                emit artistAdded(l_artist);
            }

            l_album = album(p_album, l_artist->name());
            if(!l_album)
            {
                l_album = new Album(p_album, l_artist);

                if(l_path.endsWith("flac"))
                {
                    l_album->setCover(TagLibWrapper::readFlacCover(QFileInfo(l_path)));
                }
                else if(l_path.endsWith("mp3"))
                {
                    l_album->setCover(TagLibWrapper::readMp3Cover(QFileInfo(l_path)));
                }

                l_artist->addAlbum(l_album);
                emit albumAdded(l_album);
            }

            if(l_trackTitle.length() == 0)
            {
                l_trackTitle = l_path.mid(l_path.lastIndexOf("/") + 1);
                l_trackTitle = l_trackTitle.left(l_trackTitle.lastIndexOf("."));
                p_track->setTitle(l_trackTitle);
            }

            p_track->setAlbum(l_album);
            l_album->addTrack(p_track);

            emit trackAdded(p_track);
        }
    }
}

void MusicLibrary::changeAlbumOnTrack(Track* track, QString newAlbum)
{
    Album* l_album = album(newAlbum);

    if(!l_album)
    {
        Artist* l_artist = track->album()->artist();
        l_album = new Album(newAlbum, l_artist);
        l_artist->addAlbum(l_album);
    }

    track->album()->removeTrack(track);

    track->setAlbum(l_album);
    l_album->addTrack(track);
}

Track* MusicLibrary::track(const QString& path)
{
    foreach(Artist* i_artist, m_artists)
    {
        foreach(Album* i_album, i_artist->albums())
        {
            foreach(Track* i_track, i_album->tracks())
            {
                if(i_track->path() == path)
                {
                    return i_track;
                }
            }
        }
    }

    return NULL;
}

bool MusicLibrary::exists(const QString& path)
{
    foreach(Artist* i_artist, m_artists)
    {
        foreach(Album* i_album, i_artist->albums())
        {
            foreach(Track* i_track, i_album->tracks())
            {
                if(i_track->path() == path)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void MusicLibrary::onTrackToLoad(Track* track)
{
    if(track)
    {
        QObject::connect(track, SIGNAL(trackLoaded(Track*, QString, QString)), this, SLOT(onTrackLoaded(Track*, QString, QString)));
        track->load();
    }
}

void MusicLibrary::onTracksToLoad(const QVector<QFileInfo>& filesInfo)
{
    for(QVector<QFileInfo>::ConstIterator i_file = filesInfo.begin(); i_file < filesInfo.end(); ++i_file)
    {
        if(i_file->suffix() == "flac" || i_file->suffix() == "mp3")
        {
            Track* track = new Track(i_file->canonicalFilePath());
            QObject::connect(track, SIGNAL(trackLoaded(Track*, QString, QString)), this, SLOT(onTrackLoaded(Track*, QString, QString)));
            track->load();
        }
    }
}

void MusicLibrary::onTempoChanged(QString path)
{
    QVector<QFileInfo> filesInfo;
    filesInfo.push_back(QFileInfo(path));
    onTracksToLoad(filesInfo);
}

void MusicLibrary::onArtistRemoved(Artist* artist)
{
    if(removeArtist(artist))
    {
        emit artistRemoved(artist);
    }
}

void MusicLibrary::onAlbumRemoved(Album* album)
{
    if(removeAlbum(album))
    {
        emit albumRemoved(album);
    }
}

void MusicLibrary::onTrackRemoved(Track* track)
{
    if(removeTrack(track))
    {
        emit trackRemoved(track);
    }
}
