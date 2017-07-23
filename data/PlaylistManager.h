#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QDataStream>
#include <QFile>
#include <QObject>
#include <QPointer>
#include <QVector>

#include "Playlist.h"

class PlaylistManager : public QObject
{
public:
    static PlaylistManager* instance();
    static void deleteInstance();

    QStringList playlistsName();
    const QVector<Playlist*>& playlists();

    void loadPlaylists();
    void addPlaylist(Playlist* playlist);
    void savePlaylist(Playlist* playlist);

protected:
    PlaylistManager(QObject* parent = 0);

public:
    static QPointer<PlaylistManager> m_instance;

    QVector<Playlist*> m_playlists;
};

#endif // PLAYLISTMANAGER_H
