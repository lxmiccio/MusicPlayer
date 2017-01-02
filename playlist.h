#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QVector>

#include "Track.h"

class Playlist
{
    public:
        explicit Playlist(const QString& name);

        const QString& name() const;
        void setName(const QString& name);

        const QVector<const Track*>& tracks() const;
        void addTrack(const Track& track);
        void removeTrack(const Track &track);
        void removeAllTracks();

    private:
        QVector<const Track*> c_tracks;
        QString m_name;
};

#endif // PLAYLIST_H
