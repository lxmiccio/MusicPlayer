#include "Playlist.h"

Playlist::Playlist(const QString& name, QObject* parent) : QObject(parent)
{
    m_name = name;
    m_startingIndex = 0;
}

Playlist* Playlist::fromAlbum(Album* album, Track* startingTrack)
{
    Playlist* playlist = new Playlist("Playing");

    if(album)
    {
        foreach(Track* i_track, album->tracks())
        {
            playlist->addTrack(i_track);
        }

        if(startingTrack && (album->tracks().indexOf(startingTrack) >= 0))
        {
            playlist->setStartingIndex(album->tracks().indexOf(startingTrack));
        }
    }

    return playlist;
}

Playlist* Playlist::fromTracks(QVector<Track*> tracks, Track* startingTrack)
{
    Playlist* playlist = new Playlist("Playing");

    foreach(Track* i_track, tracks)
    {
        if(i_track)
        {
            playlist->addTrack(i_track);
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
    /* Never used so far */
    Playlist* playlist = new Playlist("Playing");

    QFile inFile(file.absoluteFilePath());
    inFile.open(QIODevice::WriteOnly);
    QDataStream stream(&inFile);
    stream >> *playlist;

    return playlist;
}

void Playlist::saveToFile() const
{
    /* Never used so far */
    QFile file(QDir::currentPath() + QDir::separator() + m_name);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    stream << *this;
}

const QVector<Track*>& Playlist::tracks() const
{
    return m_tracks;
}

const QStringList& Playlist::tracksPath() const
{
    return m_tracksPath;
}

void Playlist::addTrack(Track* track)
{
    if(track)
    {
        m_tracksPath << track->path();
        m_tracks.push_back(track);
    }
}

void Playlist::removeTrack(Track* track)
{
    m_tracks.removeOne(track);
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
    m_tracks.clear();
    m_startingIndex = 0;
}

QDataStream &operator<<(QDataStream& out, const Playlist& playlist)
{
    /* Never used so far */
    out << playlist.name();
    out << playlist.tracksPath();
    return out;
}

QDataStream &operator>>(QDataStream& in, Playlist& playlist)
{
    /* Never used so far */
    QString name;
    QStringList tracksPath;

    in >> name >> tracksPath;
    return in;
}
