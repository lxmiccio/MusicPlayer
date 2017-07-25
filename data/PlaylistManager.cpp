#include "PlaylistManager.h"

#include "Settings.h"

QPointer<PlaylistManager> PlaylistManager::m_instance = NULL;

PlaylistManager::PlaylistManager(QObject* parent) : QObject(parent)
{
}

PlaylistManager* PlaylistManager::instance()
{
    if(m_instance == 0)
    {
        m_instance = new PlaylistManager();
        m_instance->loadPlaylists();
    }

    return m_instance;
}

void PlaylistManager::deleteInstance()
{
    //delete m_instance;
}

QStringList PlaylistManager::playlistsName()
{
    QStringList names;

    foreach(Playlist* playlist, m_playlists)
    {
        names << playlist->name();
    }

    return names;
}

const QVector<Playlist*>& PlaylistManager::playlists()
{
    return m_playlists;
}

void PlaylistManager::loadPlaylists()
{
    QFile file(Settings::playlistsFile());
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open" << Settings::playlistsFile();
        return;
    }

    QDataStream in(&file);
    while(!file.atEnd())
    {
        SerializablePlaylist serializable;
        in >> serializable;

        Playlist* playlist = playlistFromSerializable(serializable);
        m_playlists.push_back(playlist);
    }

    file.close();
}

void PlaylistManager::addPlaylist(Playlist* playlist)
{
    if(playlist)
    {
        m_playlists.push_back(playlist);
    }
}

void PlaylistManager::savePlaylist(Playlist* playlist)
{
    if(playlist)
    {
        m_playlists.push_back(playlist);

        QFile file(Settings::playlistsFile());
        QFile::OpenMode mode = QIODevice::WriteOnly;

        if(file.exists())
        {
            mode = QIODevice::Append;
        }

        if(!file.open(mode))
        {
            qDebug() << "Could not open" << Settings::playlistsFile();
            return;
        }

        SerializablePlaylist serializable = serializableFromPlaylist(playlist);

        QDataStream out(&file);
        out << serializable;

        file.flush();
        file.close();
    }
}

Playlist* PlaylistManager::playlistFromSerializable(SerializablePlaylist serializable)
{
    Playlist* playlist = new Playlist(serializable.m_name);

    for(quint16 i = 0; i < serializable.m_tracks.size(); ++i)
    {
        QString path = serializable.m_tracks.at(i);
        playlist->addTrack(path);
    }

    return playlist;
}

SerializablePlaylist PlaylistManager::serializableFromPlaylist(Playlist* playlist)
{
    SerializablePlaylist serializable;

    if(playlist)
    {
        serializable.m_name = playlist->name();
        foreach(Track* track, playlist->tracks())
        {
            serializable.m_tracks << track->path();
        }
    }

    return serializable;
}

QDataStream &operator<<(QDataStream& out, const SerializablePlaylist& playlist)
{
    out << playlist.m_name << playlist.m_tracks;
    return out;
}

QDataStream &operator>>(QDataStream& in, SerializablePlaylist& playlist)
{
    in >> playlist.m_name >> playlist.m_tracks;
    return in;
}
