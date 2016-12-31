#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{
    m_mediaPlayer = new QMediaPlayer();
    m_mediaPlayer->setVolume(100);

    m_mediaPlaylist = new QMediaPlaylist();
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
}

void MusicPlayer::addTrack(const Track& track)
{
    m_tracks.push_back(&track);
    m_mediaPlaylist->addMedia(track.mediaContent());
}

void MusicPlayer::addTracks(const QVector<const Track*>& tracks)
{
    foreach(const Track* i_track, tracks)
    {
        m_tracks.push_back(i_track);
        m_mediaPlaylist->addMedia(i_track->mediaContent());
    }
}

void MusicPlayer::removeTrack(const Track& track)
{
    for(int i {0}; i < m_mediaPlaylist->mediaCount(); ++i) {
        //if(m_mediaPlaylist->media(i) == track.getMediaContent()) {
        //m_mediaPlaylist->removeMedia(i);
        //break;
        //}
    }
}

void MusicPlayer::removeAllTracks()
{
    m_mediaPlaylist->clear();
}

QMediaPlayer* MusicPlayer::mediaPlayer() const
{
    return m_mediaPlayer;
}

QMediaPlaylist* MusicPlayer::mediaPlaylist() const
{
    return m_mediaPlaylist;
}
