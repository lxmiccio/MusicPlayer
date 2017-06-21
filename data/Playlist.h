#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>

#include "Album.h"
#include "Track.h"

class Playlist : public QObject
{
        Q_OBJECT

    public:
        explicit Playlist(const QString& name = QString("Playing"), QObject* parent = 0);

        static Playlist* fromAlbum(Album* album, Track* startingTrack = NULL);
        static Playlist* fromTracks(QVector<Track*> tracks, Track* startingTrack = NULL);

        static const Playlist* pathsFromPlaylist(QFileInfo& file);
        void saveToFile() const;

        const QString& name() const;
        void setName(const QString& name);

        const QStringList& tracksPath() const;

        const QVector<Track*>& tracks() const;
        void addTrack(Track* track);
        void removeTrack(Track* track);

        quint16 startingIndex();
        void setStartingIndex(quint16 startingIndex);
        void clear();

    private:
        QString m_name;
        QStringList m_tracksPath;
        QVector<Track*> m_tracks;
        quint16 m_startingIndex;
};

QDataStream &operator<<(QDataStream& out, const Playlist& playlist);
QDataStream &operator>>(QDataStream& in, Playlist& playlist);

#endif// PLAYLIST_H
