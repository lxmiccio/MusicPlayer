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
    emit artistUpdated(this, Artist::NAME);
}

const QVector<Album*>& Artist::albums() const
{
    return m_albums;
}

Album* Artist::album(const QString& title) const
{
    foreach(Album* i_album, m_albums)
    {
        if(i_album->title() == title)
        {
            return i_album;
        }
    }

    return NULL;
}

void Artist::addAlbum(Album* album)
{
    if(album)
    {
        QObject::connect(album, SIGNAL(albumUpdated(Album*, quint8)), this, SIGNAL(albumUpdate(Album*, quint8)));
        m_albums.push_back(album);

        sort();
        emit albumAdded(album);
    }
}

bool Artist::removeAlbum(Album* album)
{
    if(m_albums.removeOne(album))
    {
        emit albumRemoved(album);
        delete album;
        return true;
    }
    else
    {
        return false;
    }
}

bool Artist::removeAlbum(const QString& title)
{
    foreach(Album* i_album, m_albums)
    {
        if(i_album->title() == title)
        {
            return removeAlbum(i_album);
        }
    }

    return false;
}

const QVector<Track*> Artist::tracks() const
{
    QVector<Track*> tracks;

    foreach(Album* i_album, m_albums)
    {
        foreach(Track* i_track, i_album->tracks())
        {
            tracks.push_back(i_track);
        }
    }

    return tracks;
}

void Artist::sort()
{
    std::sort(m_albums.begin(), m_albums.end(), [] (const Album* album1, const Album* album2) -> bool
    {
        return album1->title() < album2->title();
    });
}

bool operator==(const Artist& artist1, const Artist& artist2)
{
    return artist1.name() == artist2.name();
}

bool operator<(const Artist& artist1, const Artist& artist2)
{
    return artist1.name() < artist2.name();
}
