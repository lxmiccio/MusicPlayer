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

Playlist* PlaylistManager::playlist(const QString& name)
{
    foreach(Playlist* i_playlist, m_playlists)
    {
        if(i_playlist->name() == name)
        {
            return i_playlist;
        }
    }

    return NULL;
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
        QObject::connect(playlist, SIGNAL(playlistUpdated()), SLOT(onPlaylistUpdated()));

        m_playlists.push_back(playlist);
    }

    file.close();

    sort();
}


void PlaylistManager::savePlaylist(Playlist* playlist)
{
    if(playlist)
    {
        QObject::connect(playlist, SIGNAL(playlistUpdated()), SLOT(onPlaylistUpdated()));

        if(!m_playlists.contains(playlist))
        {
            m_playlists.push_back(playlist);
            sort();
        }

        QFile file(Settings::playlistsFile());
        QFile::OpenMode mode = QIODevice::WriteOnly;

        if(!file.open(mode))
        {
            qDebug() << "Could not open" << Settings::playlistsFile();
            return;
        }

        foreach(Playlist* i_playlist, m_playlists)
        {
            SerializablePlaylist serializable = serializableFromPlaylist(i_playlist);

            QDataStream out(&file);
            out << serializable;
        }

        file.flush();
        file.close();
    }
}

void PlaylistManager::sort()
{
    std::sort(m_playlists.begin(), m_playlists.end(), [] (const Playlist* playlist1, const Playlist* playlist2) -> bool
    {
        return playlist1->name() < playlist2->name();
    });
}

void PlaylistManager::onPlaylistUpdated()
{
    Playlist* playlist = static_cast<Playlist*>(QObject::sender());

    if(!playlist || playlist->tracks().isEmpty())
    {
        m_playlists.removeOne(playlist);
        playlist->deleteLater();

        emit playlistsChanged();
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
