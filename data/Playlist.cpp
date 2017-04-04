#include "Playlist.h"

Playlist::Playlist() : m_startingIndex(0)
{
}

Playlist* Playlist::fromAlbum(const Album* album, const Track* startingTrack)
{
    Playlist* playlist = new Playlist();

    if(album)
    {
        foreach(Track* i_track, album->tracks())
        {
            playlist->addTrack(*i_track);
        }

        if(startingTrack && (album->tracks().indexOf(const_cast<Track*>(startingTrack)) >= 0))
        {
            playlist->setStartingIndex(album->tracks().indexOf(const_cast<Track*>(startingTrack)));
        }
    }

    return playlist;
}

Playlist* Playlist::fromTracks(const QVector<const Track*> tracks, const Track* startingTrack)
{
    Playlist* playlist = new Playlist();

    foreach(const Track* i_track, tracks)
    {
        if(i_track)
        {
            playlist->addTrack(*i_track);
        }
    }

    if(startingTrack && (tracks.indexOf(startingTrack) >= 0))
    {
        playlist->setStartingIndex(tracks.indexOf(startingTrack));
    }

    return playlist;
}

const Playlist* Playlist::pathsFromPlaylist(QFileInfo& file)
{
    Playlist* playlist = new Playlist();

    QFile inFile(file.absoluteFilePath());
    inFile.open(QIODevice::WriteOnly);
    QDataStream stream(&inFile);
    stream >> *playlist;

    return playlist;
}

void Playlist::saveToFile() const
{
    QFile file(QDir::currentPath() + QDir::separator() + m_name);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    stream << *this;
}

const QVector<const Track*>& Playlist::tracks() const
{
    return c_tracks;
}

const QStringList& Playlist::tracksPath() const
{
    return m_tracksPath;
}

void Playlist::addTrack(const Track& track)
{
    m_tracksPath << track.title();
    c_tracks.push_back(&track);
}

void Playlist::removeTrack(const Track& track)
{
    c_tracks.removeOne(&track);
}

const QString& Playlist::name() const
{
    return m_name;
}

void Playlist::setName(const QString& name)
{
    m_name = name;
}

quint16 Playlist::startingIndex()
{
    return m_startingIndex;
}

void Playlist::setStartingIndex(quint16 startingIndex)
{
    m_startingIndex = startingIndex;
}

void Playlist::clear()
{
    c_tracks.clear();
    m_startingIndex = 0;
}

QDataStream &operator<<(QDataStream &out, const Playlist& playlist)
{
    out << playlist.name();
    out << playlist.tracksPath();
    return out;
}

QDataStream &operator>>(QDataStream &in, Playlist& playlist)
{
    QString name;
    QStringList tracksPath;

    in >> name >> tracksPath;
    return in;
}
