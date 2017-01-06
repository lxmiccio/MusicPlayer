#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(QObject* parent) : QObject(parent)
{
    m_playlist = new Playlist();

    m_mediaPlaylist = new QMediaPlaylist();
    QObject::connect(m_mediaPlaylist, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));

    m_mediaPlayer = new QMediaPlayer();
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
    m_mediaPlayer->setVolume(100);
    QObject::connect(m_mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
}

QMediaPlayer* MusicPlayer::mediaPlayer() const
{
    return m_mediaPlayer;
}

QMediaPlaylist* MusicPlayer::mediaPlaylist() const
{
    return m_mediaPlaylist;
}

void MusicPlayer::onTrackSelected(const Track& track)
{
    m_playlist->removeAllTracks();
    m_mediaPlaylist->clear();

    Track* trackSelected = const_cast<Track*>(&track);

    for(int i = track.album()->tracks().indexOf(trackSelected); i < track.album()->tracks().size(); i++)
    {
        m_playlist->addTrack(*track.album()->tracks().at(i));
        m_mediaPlaylist->addMedia(QUrl::fromLocalFile(track.album()->tracks().at(i)->path()));
    }

    emit trackStarted(track);
    m_mediaPlayer->play();
}

void MusicPlayer::onBackwardClicked()
{
    if(m_mediaPlaylist->currentIndex() == 0)
    {
        m_mediaPlayer->stop();
    }
    else
    {
        m_mediaPlaylist->previous();
    }
}

void MusicPlayer::onPlayClicked()
{
    m_mediaPlayer->play();
}

void MusicPlayer::onPauseClicked()
{
    m_mediaPlayer->pause();
}

void MusicPlayer::onForwardClicked()
{
    if(m_mediaPlaylist->currentIndex() == m_mediaPlaylist->mediaCount() - 1)
    {
        m_mediaPlayer->stop();
    }
    else
    {
        m_mediaPlaylist->next();
    }
}

void MusicPlayer::onTrackValueChanged(int value)
{
    m_mediaPlayer->setPosition(value);
}

void MusicPlayer::onShuffleClicked(AudioControls::ShuffleMode_t shuffleMode)
{
    switch (shuffleMode)
    {
        case AudioControls::SHUFFLE_OFF:
        {
            m_mediaPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);
            break;
        }

        case AudioControls::SHUFFLE_ON:
        {
            m_mediaPlaylist->setPlaybackMode(QMediaPlaylist::Random);
            break;
        }

        default:
        {
            break;
        }
    }
}

void MusicPlayer::onRepeatClicked(AudioControls::RepeatMode_t repeatMode)
{
    switch (repeatMode)
    {
        case AudioControls::REPEAT_NONE:
        {
            m_mediaPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);
            break;
        }

        case AudioControls::REPEAT_ONE:
        {
            m_mediaPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            break;
        }

        case AudioControls::REPEAT_ALL:
        {
            m_mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
            break;
        }

        default:
        {
            break;
        }
    }
}

void MusicPlayer::onVolumeClicked(AudioControls::VolumeMode_t volumeMode)
{
    switch (volumeMode)
    {
        case AudioControls::VOLUME_MUTED:
        {
            m_mediaPlayer->setMuted(true);
            break;
        }

        case AudioControls::VOLUME_NOT_MUTED:
        {
            m_mediaPlayer->setMuted(false);
            break;
        }

        default:
        {
            break;
        }
    }
}

void MusicPlayer::onVolumeValueChanged(int value)
{
    m_mediaPlayer->setVolume(value);
}

void MusicPlayer::onCurrentIndexChanged(int index)
{
    emit trackFinished();

    if(index >= 0 && index < m_playlist->tracks().size())
    {
        emit trackStarted(*m_playlist->tracks().at(index));
    }
}

void MusicPlayer::onPositionChanged(qint64 position)
{
    emit positionChanged(position, m_mediaPlayer->duration());
}
