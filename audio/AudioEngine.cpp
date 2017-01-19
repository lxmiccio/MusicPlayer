#include "AudioEngine.h"

AudioEngine::AudioEngine(QObject* parent) : QObject(parent)
{
    m_playlist = new Playlist();

    m_mediaPlaylist = new QMediaPlaylist();

    m_mediaPlayer = new QMediaPlayer();
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
    m_mediaPlayer->setVolume(100);

    QObject::connect(m_mediaPlaylist, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
    QObject::connect(m_mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    QObject::connect(this, SIGNAL(trackStarted(const Track&)), this, SLOT(onTrackStarted()));
}

void AudioEngine::onTrackSelected(const Track& track)
{
    m_playlist->clear();
    m_mediaPlaylist->clear();

    const Album* album = track.album();

    if(album)
    {
        for(int i = album->tracks().indexOf(const_cast<Track*>(&track)); i < album->tracks().size(); i++)
        {
            m_playlist->addTrack(*album->tracks().at(i));
            m_mediaPlaylist->addMedia(QUrl::fromLocalFile(album->tracks().at(i)->path()));
        }
    }
    else
    {
        m_playlist->addTrack(track);
        m_mediaPlaylist->addMedia(QUrl::fromLocalFile(track.path()));
    }

    emit trackStarted(track);
}

void AudioEngine::onBackwardClicked()
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

void AudioEngine::onPlayClicked()
{
    m_mediaPlayer->play();
}

void AudioEngine::onPauseClicked()
{
    m_mediaPlayer->pause();
}

void AudioEngine::onForwardClicked()
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

void AudioEngine::onTrackValueChanged(int value)
{
    m_mediaPlayer->setPosition(value);
}

void AudioEngine::onShuffleClicked(AudioControls::ShuffleMode_t shuffleMode)
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

void AudioEngine::onRepeatClicked(AudioControls::RepeatMode_t repeatMode)
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

void AudioEngine::onVolumeClicked(AudioControls::VolumeMode_t volumeMode)
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

void AudioEngine::onVolumeValueChanged(int value)
{
    m_mediaPlayer->setVolume(value);
}

void AudioEngine::onCurrentIndexChanged(int index)
{
    emit trackFinished();

    if(index >= 0 && index < m_playlist->tracks().size())
    {
        emit trackStarted(*m_playlist->tracks().at(index));
    }
}

void AudioEngine::onPositionChanged(qint64 position)
{
    emit positionChanged(position);

    if(m_mediaPlaylist->playbackMode() == QMediaPlaylist::CurrentItemInLoop)
    {
        if(position >= m_mediaPlayer->duration())
        {
            emit trackFinished();
            emit trackStarted(*m_playlist->tracks().at(m_mediaPlaylist->currentIndex()));
        }
    }
}

void AudioEngine::onTrackStarted()
{
    m_mediaPlayer->play();
}
