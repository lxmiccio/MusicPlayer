#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QVector>

#include "Album.h"
#include "Track.h"

class Playlist
{
    public:
        explicit Playlist();

        static Playlist* fromAlbum(const Album* album, const Track* startingTrack = NULL);
        static Playlist* fromTracks(const QVector<const Track*> tracks, const Track* startingTrack = NULL);

        static const Playlist* pathsFromPlaylist(QFileInfo& file);
        void saveToFile() const;

        const QString& name() const;
        void setName(const QString& name);

        const QStringList& tracksPath() const;

        const QVector<const Track*>& tracks() const;
        void addTrack(const Track& track);
        void removeTrack(const Track &track);

        quint16 startingIndex();
        void setStartingIndex(quint16 startingIndex);
        void clear();

    private:
        QString m_name;
        QStringList m_tracksPath;
        QVector<const Track*> c_tracks;
        quint16 m_startingIndex;
};

QDataStream &operator<<(QDataStream &out, const Playlist &playlist);
QDataStream &operator>>(QDataStream &in, Playlist &playlist);

#endif // PLAYLIST_H
