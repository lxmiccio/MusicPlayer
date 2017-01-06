#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QVector>

#include "Track.h"

class Playlist
{
    public:
        Playlist();

        const QVector<const Track*>& tracks() const;
        void addTrack(const Track& track);
        void removeTrack(const Track &track);
        void clear();

    private:
        QVector<const Track*> c_tracks;
};

#endif // PLAYLIST_H
