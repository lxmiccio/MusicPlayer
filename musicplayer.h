#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "playlist.h"
#include "Track.h"

class MusicPlayer
{
    public:
        MusicPlayer();

        Playlist* playlist() const;
        void setPlaylist(Playlist& playlist);

        QMediaPlayer* mediaPlayer() const;
        QMediaPlaylist* mediaPlaylist() const;

    private:
        Playlist* m_playlist;

        QMediaPlayer* m_mediaPlayer;
        QMediaPlaylist* m_mediaPlaylist;
};

#endif // MUSICPLAYER_H
