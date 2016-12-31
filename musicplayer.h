#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Track.h"

class MusicPlayer
{
    public:
        MusicPlayer();

        void addTrack(const Track& track);
        void addTracks(const QVector<const Track*>& tracks);
        void removeTrack(const Track& track);
        void removeAllTracks();

        QMediaPlayer* mediaPlayer() const;
        QMediaPlaylist* mediaPlaylist() const;

    private:
        QVector<const Track*> m_tracks;

        QMediaPlayer* m_mediaPlayer;
        QMediaPlaylist* m_mediaPlaylist;
};

#endif // MUSICPLAYER_H
