#include "Artist.h"

Artist::Artist(QObject* parent) : QObject(parent)
{
}

Artist::Artist(const QString& name, QObject* parent) : QObject(parent)
{
    m_name = name;
}

const QString& Artist::name() const
{
    return m_name;
}

void Artist::setName(const QString& name)
{
    m_name = name;
}

const QVector<Album*>& Artist::albums() const
{
    return m_albums;
}

Album* Artist::album(const QString& title) const
{
    foreach(Album* i_album, m_albums) {
        if(i_album->title() == title) {
            return i_album;
        }
    }

    return NULL;
}

void Artist::addAlbum(Album* album)
{
    if(album) {
        m_albums.push_back(album);
        std::sort(m_albums.begin(), m_albums.end(), [] (const Album* album1, const Album* album2) -> bool {
            return album1->title() < album2->title();
        });
    }
}

bool Artist::removeAlbum(Album* album)
{
    return m_albums.removeOne(album);
}

bool Artist::removeAlbum(const QString& title)
{
    foreach(Album* i_album, m_albums) {
        if(i_album->title() == title) {
            return m_albums.removeOne(i_album);
        }
    }

    return false;
}

const QVector<Track*> Artist::tracks() const
{
    QVector<Track*> tracks;

    foreach(Album* i_album, m_albums) {
        foreach(Track* i_track, i_album->tracks()) {
            tracks.push_back(i_track);
        }
    }

    return tracks;
}

bool operator==(const Artist& artist1, const Artist& artist2)
{
    return artist1.name() == artist2.name();
}

bool operator<(const Artist& artist1, const Artist& artist2)
{
    return artist1.name() < artist2.name();
}
