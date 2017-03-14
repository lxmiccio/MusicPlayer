#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QVector>

#include "Album.h"
#include "Track.h"

class Playlist
{
    public:
        explicit Playlist();

        static Playlist* fromAlbum(const Album* album, const Track* startingTrack = NULL);
        static Playlist* fromTracks(const QVector<const Track*> tracks, const Track* startingTrack = NULL);

        const QVector<const Track*>& tracks() const;
        void addTrack(const Track& track);
        void removeTrack(const Track &track);

        quint16 startingIndex();
        void setStartingIndex(quint16 startingIndex);
        void clear();

    private:
        QVector<const Track*> c_tracks;
        quint16 m_startingIndex;
};

#endif // PLAYLIST_H
