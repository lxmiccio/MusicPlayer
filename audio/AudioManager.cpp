#include "AudioManager.h"

AudioManager::AudioManager(QWidget* parent) : QWidget(parent)
{
    m_audioEngine = AudioEngine::instance();
    m_audioControls = new AudioControls();

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_audioControls);
    setLayout(m_layout);

    QObject::connect(this, SIGNAL(trackSelected(const Track&)), m_audioEngine, SLOT(onTrackSelected(const Track&)));

    QObject::connect(m_audioEngine, SIGNAL(trackStarted(const Track&)), m_audioControls, SLOT(onTrackStarted(const Track&)));
    QObject::connect(m_audioEngine, SIGNAL(positionChanged(qint64)), m_audioControls, SLOT(onPositionChanged(qint64)));
    QObject::connect(m_audioEngine, SIGNAL(trackFinished()), m_audioControls, SLOT(onTrackFinished()));

    QObject::connect(m_audioControls, SIGNAL(backwardClicked()), m_audioEngine, SLOT(onBackwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(playClicked()), m_audioEngine, SLOT(onPlayClicked()));
    QObject::connect(m_audioControls, SIGNAL(pauseClicked()), m_audioEngine, SLOT(onPauseClicked()));
    QObject::connect(m_audioControls, SIGNAL(forwardClicked()), m_audioEngine, SLOT(onForwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(trackValueChanged(int)), m_audioEngine, SLOT(onTrackValueChanged(int)));
    QObject::connect(m_audioControls, SIGNAL(shuffleClicked(AudioControls::ShuffleMode_t)), m_audioEngine, SLOT(onShuffleClicked(AudioControls::ShuffleMode_t)));
    QObject::connect(m_audioControls, SIGNAL(repeatClicked(AudioControls::RepeatMode_t)), m_audioEngine, SLOT(onRepeatClicked(AudioControls::RepeatMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeClicked(AudioControls::VolumeMode_t)), m_audioEngine, SLOT(onVolumeClicked(AudioControls::VolumeMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeValueChanged(int)), m_audioEngine, SLOT(onVolumeValueChanged(int)));

    QObject::connect(m_audioEngine, SIGNAL(trackStarted(const Track&)), this, SLOT(onTrackStarted(const Track&)));
}

void AudioManager::onTrackSelected(const Track& track)
{
    emit trackSelected(track);
}

void AudioManager::onTrackStarted(const Track& track)
{
    emit trackStarted(track);
}
