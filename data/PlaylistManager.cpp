#include "PlaylistManager.h"

QPointer<PlaylistManager> PlaylistManager::m_instance = 0;

PlaylistManager::PlaylistManager(QObject* parent) : QObject(parent)
{
loadPlaylists();
}

PlaylistManager* PlaylistManager::instance()
{
    if(!m_instance)
    {
        m_instance = new PlaylistManager();
    }

    return m_instance;
}

void PlaylistManager::deleteInstance()
{
    delete m_instance;
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
        QString filename = "playlists.ply";
        QFile file(filename);

        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug().nospace() << "Could not open playlists.ply";
            return;
        }

        QDataStream in(&file);

        while(!file.atEnd())
        {
            Playlist playlist;
            in >> playlist;
            qDebug() << playlist.name();
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
        addPlaylist(playlist);

        QFile file(playlist->name() + ".ply");

        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug().nospace() << "Could not open " << playlist->name() << ".ply";
            return;
        }

        QDataStream out(&file);
        out << playlist;

        file.flush();
        file.close();
    }
}
