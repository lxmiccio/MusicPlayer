#include "AudioEngine.h"

AudioEngine::AudioEngine(QObject* parent) : QObject(parent)
{
    m_audioControls = new AudioControls();

    m_musicPlayer = new MusicPlayer();
    QObject::connect(this, SIGNAL(trackSelected(const Track&)), m_musicPlayer, SLOT(onTrackSelected(const Track&)));

    QObject::connect(m_audioControls, SIGNAL(backwardClicked()), m_musicPlayer, SLOT(onBackwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(playClicked()), m_musicPlayer, SLOT(onPlayClicked()));
    QObject::connect(m_audioControls, SIGNAL(pauseClicked()), m_musicPlayer, SLOT(onPauseClicked()));
    QObject::connect(m_audioControls, SIGNAL(forwardClicked()), m_musicPlayer, SLOT(onForwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(trackValueChanged(int)), m_musicPlayer, SLOT(onTrackValueChanged(int)));
    QObject::connect(m_audioControls, SIGNAL(shuffleClicked(AudioControls::ShuffleMode_t)), m_musicPlayer, SLOT(onShuffleClicked(AudioControls::ShuffleMode_t)));
    QObject::connect(m_audioControls, SIGNAL(repeatClicked(AudioControls::RepeatMode_t)), m_musicPlayer, SLOT(onRepeatClicked(AudioControls::RepeatMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeClicked(AudioControls::VolumeMode_t)), m_musicPlayer, SLOT(onVolumeClicked(AudioControls::VolumeMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeValueChanged(int)), m_musicPlayer, SLOT(onVolumeValueChanged(int)));

    QObject::connect(m_musicPlayer, SIGNAL(trackStarted(const Track&)), m_audioControls, SLOT(onTrackStarted(const Track&)));
    QObject::connect(m_musicPlayer, SIGNAL(trackFinished()), m_audioControls, SLOT(onTrackFinished()));
}

AudioControls* AudioEngine::audioControls()
{
    return m_audioControls;
}

void AudioEngine::onTrackSelected(const Track &track)
{
    emit trackSelected(track);
}
