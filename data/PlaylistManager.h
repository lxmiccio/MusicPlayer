#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QDataStream>
#include <QFile>
#include <QObject>
#include <QPointer>
#include <QVector>

#include "Playlist.h"

class SerializablePlaylist
{
    public:
        QString m_name;
        QStringList m_tracks;
};

QDataStream &operator<<(QDataStream& out, const SerializablePlaylist& playlist);
QDataStream &operator>>(QDataStream& in, SerializablePlaylist& playlist);

class PlaylistManager : public QObject
{
    public:
        static PlaylistManager* instance();
        static void deleteInstance();

        QStringList playlistsName();
        const QVector<Playlist*>& playlists();

        Playlist* playlist(const QString& name);

        void loadPlaylists();
        void addPlaylist(Playlist* playlist);
        void savePlaylist(Playlist* playlist);

        void sort();

        Playlist* playlistFromSerializable(SerializablePlaylist serializable);
        SerializablePlaylist serializableFromPlaylist(Playlist* playlist);

    protected:
        PlaylistManager(QObject* parent = 0);

    private:
        static QPointer<PlaylistManager> m_instance;

        QVector<Playlist*> m_playlists;
};

#endif // PLAYLISTMANAGER_H
