#include "AudioEngine.h"

QPointer<AudioEngine> AudioEngine::m_instance = 0;

AudioEngine::AudioEngine()
{
    m_playlist = NULL;

    m_mediaPlaylist = new QMediaPlaylist();

    m_mediaPlayer = new QMediaPlayer();
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
    m_mediaPlayer->setVolume(Settings::volume());

    QObject::connect(m_mediaPlaylist, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
    QObject::connect(m_mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    QObject::connect(this, SIGNAL(trackStarted(const Track*)), this, SLOT(onTrackStarted()));
}

AudioEngine::~AudioEngine()
{
}

AudioEngine* AudioEngine::instance()
{
    if(m_instance.isNull())
    {
        m_instance = new AudioEngine();
    }

    return m_instance;
}

void AudioEngine::close()
{
    delete m_instance;
}

Playlist* AudioEngine::playlist()
{
    return m_playlist;
}

void AudioEngine::onPlaylistSelected(Playlist* playlist)
{
    if(playlist && !playlist->tracks().isEmpty())
    {
        m_playlist = playlist;
        m_mediaPlaylist->clear();

        foreach(const Track* i_track, m_playlist->tracks())
        {
            m_mediaPlaylist->addMedia(QUrl::fromLocalFile(i_track->path()));
        }

        m_mediaPlaylist->setCurrentIndex(playlist->startingIndex());

        emit trackStarted(m_playlist->tracks().at(playlist->startingIndex()));
    }
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
    Settings::setVolume(value);
}

void AudioEngine::onCurrentIndexChanged(int index)
{
    emit trackFinished();

    if(index >= 0 && index < m_playlist->tracks().size())
    {
        emit trackStarted(m_playlist->tracks().at(index));
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
            emit trackStarted(m_playlist->tracks().at(m_mediaPlaylist->currentIndex()));
        }
    }
}

void AudioEngine::onTrackStarted()
{
    m_mediaPlayer->play();
}
