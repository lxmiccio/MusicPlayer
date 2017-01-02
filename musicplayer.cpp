#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{
    m_mediaPlayer = new QMediaPlayer();
    m_mediaPlayer->setVolume(100);

    m_mediaPlaylist = new QMediaPlaylist();
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
}

Playlist* MusicPlayer::playlist() const
{
    return m_playlist;
}

void MusicPlayer::setPlaylist(Playlist& playlist)
{
    m_playlist = &playlist;

    m_mediaPlayer->setMedia(QUrl::fromLocalFile(playlist.tracks().at(0)->path()));
    m_mediaPlayer->play();
}

QMediaPlayer* MusicPlayer::mediaPlayer() const
{
    return m_mediaPlayer;
}

QMediaPlaylist* MusicPlayer::mediaPlaylist() const
{
    return m_mediaPlaylist;
}
