#include "MusicLibrary.h"

#include "TagUtils.h"

QPointer<MusicLibrary> MusicLibrary::m_instance = 0;

MusicLibrary::MusicLibrary()
{
    m_trackLoader = new TrackLoader();
    QObject::connect(m_trackLoader, SIGNAL(tagsRead(QVariantMap*)), this, SLOT(addTrack(QVariantMap*)));
}

MusicLibrary* MusicLibrary::instance()
{
    if(m_instance.isNull()) {
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
    foreach(Artist* i_artist, m_artists) {
        if(i_artist->name() == name) {
            return i_artist;
        }
    }

    return NULL;
}

bool MusicLibrary::removeArtist(Artist* artist)
{
    QMutexLocker locker(&m_mutex);
    return m_artists.removeOne(artist);
}

bool MusicLibrary::removeArtist(const QString& name)
{
    QMutexLocker locker(&m_mutex);
    return m_artists.removeOne(artist(name));
}

const QVector<Album*> MusicLibrary::albums() const
{
    QVector<Album*> albums;

    foreach(Artist* i_artist, m_artists) {
        foreach(Album* i_album, i_artist->albums()) {
            albums.push_back(i_album);
        }
    }

    return albums;
}

Album* MusicLibrary::album(const QString& title) const
{
    foreach(Artist* i_artist, m_artists) {
        foreach(Album* i_album, i_artist->albums()) {
            if(i_album->title() == title) {
                return i_album;
            }
        }
    }

    return NULL;
}

Album* MusicLibrary::album(const QString& title, const QString& artistName) const
{
    foreach(Artist* i_artist, m_artists) {
        if(i_artist->name() == artistName) {
            foreach(Album* i_album, i_artist->albums()) {
                if(i_album->title() == title) {
                    return i_album;
                }
            }
        }
    }

    return NULL;
}

bool MusicLibrary::removeAlbum(Album* album)
{
    QMutexLocker locker(&m_mutex);

    foreach(Artist* i_artist, m_artists) {
        if(i_artist->removeAlbum(album)) {
            return true;
        }
    }

    return false;
}

bool MusicLibrary::removeAlbum(const QString& albumName, const QString& artistName)
{
    QMutexLocker locker(&m_mutex);

    if(artist(artistName)) {
        return artist(artistName)->removeAlbum(albumName);
    } else {
        return false;
    }
}

const QVector<Track*> MusicLibrary::tracks() const
{
    QVector<Track*> tracks;

    foreach(Artist* i_artist, m_artists) {
        foreach(Album* i_album, i_artist->albums()) {
            foreach(Track *i_track, i_album->tracks()) {
                tracks.push_back(i_track);
            }
        }
    }

    return tracks;
}

bool MusicLibrary::removeTrack(Track* track)
{
    QMutexLocker locker(&m_mutex);

    foreach(Artist* i_artist, m_artists) {
        foreach(Album* i_album, i_artist->albums()) {
            if(i_album->removeTrack(track)) {
                return true;
            }
        }
    }

    return false;
}

bool MusicLibrary::removeTrack(const QString& trackTitle, const QString& albumTitle)
{
    QMutexLocker locker(&m_mutex);

    if(album(albumTitle) != NULL) {
        return album(albumTitle)->removeTrack(trackTitle);
    }

    return false;
}

void MusicLibrary::addTrack(QVariantMap* tags)
{
    if(tags)
    {
        QMutexLocker locker(&m_mutex);

        Artist* l_artist = NULL;
        Album* l_album = NULL;
        Track* l_track = NULL;

        if(tags->value("duration", 0).toInt() > 0)
        {
            QString l_artistName = tags->value("artist", "Unknown").toString();
            QString l_albumTitle = tags->value("album", "Unknown").toString();
            QString l_path = tags->value("path", "Unknown").toString();
            QString l_trackTitle = tags->value("title", "").toString();

            l_artist = artist(l_artistName);
            if(!l_artist)
            {
                l_artist = new Artist(l_artistName);
                m_artists.push_back(l_artist);
                emit artistAdded(l_artist);
            }

            l_album = album(l_albumTitle, l_artist->name());
            if(!l_album)
            {
                l_album = new Album(l_albumTitle, l_artist);

                //TODO: Cover should be loaded on a different thread
                if(l_path.endsWith(".flac"))
                {
                    l_album->setCover(TagUtils::readFlacCover(QFileInfo(l_path)));
                }
                else if(l_path.endsWith(".mp3"))
                {
                    l_album->setCover(TagUtils::readMp3Cover(QFileInfo(l_path)));
                }

                l_artist->addAlbum(l_album);
                emit albumAdded(l_album);
            }

            if(l_trackTitle.length() == 0)
            {
                l_trackTitle = l_path.mid(l_path.lastIndexOf("/") + 1);
                l_trackTitle = l_trackTitle.left(l_trackTitle.lastIndexOf("."));
                tags->insert("title", l_trackTitle);
            }

            l_track = const_cast<Track*>(l_album->track(l_trackTitle));
            if(!l_track)
            {
                //TODO: Load lyrics

                l_track = new Track(*tags, l_album);
                l_album->addTrack(l_track);
                emit trackAdded(l_track);
            }
        }

        delete tags;
    }
}

void MusicLibrary::onTracksToLoad(const QVector<QFileInfo>& filesInfo)
{
    m_trackLoader->readTags(filesInfo);
}

void MusicLibrary::onArtistRemoved(const Artist* artist)
{
    if(removeArtist(const_cast<Artist*>(artist)))
        emit artistRemoved(artist);
}

void MusicLibrary::onAlbumRemoved(const Album* album)
{
    if(removeAlbum(const_cast<Album*>(album)))
        emit albumRemoved(album);
}

void MusicLibrary::onTrackRemoved(const Track* track)
{
    if(removeTrack(const_cast<Track*>(track)))
        emit trackRemoved(track);
}
