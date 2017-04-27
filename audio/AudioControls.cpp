#include "AudioControls.h"

#include "AudioEngine.h"

AudioControls::AudioControls(QWidget* parent) : QWidget(parent), m_volumeShortcut(QKeySequence(Qt::CTRL + Qt::Key_M), true)
{
    QSizePolicy sizePolicy;

    QFont font = QApplication::font();
    font.setPointSize(13);

    m_repeatMode = AudioControls::REPEAT_NONE;
    m_shuffleMode = AudioControls::SHUFFLE_OFF;
    m_volumeMode = AudioControls::VOLUME_NOT_MUTED;

    m_upperSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding);

    m_artist = new ClickableLabel();
    m_artist->hide();
    m_artist->setFont(font);
    m_artist->setStyleSheet(QString("color: white;"));

    m_dash = new QLabel("-");
    m_dash->hide();
    m_dash->setFont(font);
    m_dash->setStyleSheet(QString("color: white;"));
    sizePolicy = m_dash->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_dash->setSizePolicy(sizePolicy);

    m_track = new ClickableLabel();
    m_track->hide();
    m_track->setFont(font);
    m_track->setStyleSheet(QString("color: white;"));

    m_upperSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding);

    m_upperHorizontalLayout = new QHBoxLayout();
    m_upperHorizontalLayout->addItem(m_upperSpacer1);
    m_upperHorizontalLayout->addWidget(m_artist);
    m_upperHorizontalLayout->addWidget(m_dash);
    m_upperHorizontalLayout->addWidget(m_track);
    m_upperHorizontalLayout->addItem(m_upperSpacer2);

    m_backward = new ImageButton();
    m_backward->setPixmap(ImageUtils::pixmap(QString(":/svg/backward.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_backward->setPixmap(ImageUtils::pixmap(QString(":/svg/backward.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);

    m_lowerSpacer1 = new QSpacerItem(16, 0, QSizePolicy::Fixed);

    m_play = new ImageButton();
    m_play->setPixmap(ImageUtils::pixmap(QString(":/svg/play.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_play->setPixmap(ImageUtils::pixmap(QString(":/svg/play.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);

    m_pause = new ImageButton();
    m_pause->hide();
    m_pause->setPixmap(ImageUtils::pixmap(QString(":/svg/pause.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_pause->setPixmap(ImageUtils::pixmap(QString(":/svg/pause.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);

    m_lowerSpacer2 = new QSpacerItem(16, 0, QSizePolicy::Fixed);

    m_forward = new ImageButton();
    m_forward->setPixmap(ImageUtils::pixmap(QString(":/svg/forward.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_forward->setPixmap(ImageUtils::pixmap(QString(":/svg/forward.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);

    m_lowerSpacer3 = new QSpacerItem(204, 0, QSizePolicy::Fixed);

    font.setPointSize(9);

    m_elapsedTime = new QLabel("00:00");
    m_elapsedTime->hide();
    m_elapsedTime->setFont(font);
    m_elapsedTime->setStyleSheet(QString("color: white; margin-top: -2px;"));
    m_elapsedTime->setMinimumWidth(30);
    sizePolicy = m_elapsedTime->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_elapsedTime->setSizePolicy(sizePolicy);

    m_lowerSpacer4 = new QSpacerItem(6, 0, QSizePolicy::Fixed);

    m_trackSlider = new TrackSlider(Qt::Horizontal);
    m_trackSlider->setFixedHeight(6);
    m_trackSlider->setMinimumWidth(256);
    m_trackSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_trackSlider->setValue(0);
    sizePolicy = m_trackSlider->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_trackSlider->setSizePolicy(sizePolicy);

    m_lowerSpacer5 = new QSpacerItem(6, 0, QSizePolicy::Fixed);

    m_remainingTime = new QLabel("00:00");
    m_remainingTime->hide();
    m_remainingTime->setFont(font);
    m_remainingTime->setStyleSheet(QString("color: white; margin-top: -2px;"));
    m_remainingTime->setMinimumWidth(30);
    sizePolicy = m_remainingTime->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_remainingTime->setSizePolicy(sizePolicy);

    m_lowerSpacer6 = new QSpacerItem(36, 0, QSizePolicy::Fixed);

    m_shuffle = new ImageButton();
    m_shuffle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);

    m_lowerSpacer7 = new QSpacerItem(36, 0, QSizePolicy::Fixed);

    m_repeat = new ImageButton();
    m_repeat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);

    m_lowerSpacer8 = new QSpacerItem(36, 0, QSizePolicy::Fixed);

    m_volume = new ImageButton();
    m_volume->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::white));
    m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::gray), QIcon::Off, QIcon::Active);

    m_volumeSlider = new Slider(Qt::Horizontal);
    m_volumeSlider->setAcceptWheelEvents(true);
    m_volumeSlider->setFixedHeight(6);
    m_volumeSlider->setMinimumWidth(120);
    m_volumeSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_volumeSlider->setValue(Settings::volume());

    m_lowerHorizontalLayout = new QHBoxLayout();
    m_lowerHorizontalLayout->addWidget(m_backward);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer1);
    m_lowerHorizontalLayout->addWidget(m_play);
    m_lowerHorizontalLayout->addWidget(m_pause);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer2);
    m_lowerHorizontalLayout->addWidget(m_forward);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer3);
    m_lowerHorizontalLayout->addWidget(m_elapsedTime);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer4);
    m_lowerHorizontalLayout->addWidget(m_trackSlider);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer5);
    m_lowerHorizontalLayout->addWidget(m_remainingTime);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer6);
    m_lowerHorizontalLayout->addWidget(m_shuffle);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer7);
    m_lowerHorizontalLayout->addWidget(m_repeat);
    m_lowerHorizontalLayout->addItem(m_lowerSpacer8);
    m_lowerHorizontalLayout->addWidget(m_volume);
    m_lowerHorizontalLayout->addWidget(m_volumeSlider);

    m_verticalLayout = new QVBoxLayout();
    m_verticalLayout->setContentsMargins(40, 12, 40, 16);
    m_verticalLayout->setSpacing(8);
    m_verticalLayout->addLayout(m_upperHorizontalLayout);
    m_verticalLayout->addLayout(m_lowerHorizontalLayout);

    setLayout(m_verticalLayout);

    QObject::connect(m_artist, SIGNAL(clicked()), SIGNAL(currentTrackClicked()));
    QObject::connect(m_track, SIGNAL(clicked()), SIGNAL(currentTrackClicked()));

    QObject::connect(this, SIGNAL(pauseClicked()), m_trackSlider, SLOT(onTrackPaused()));
    QObject::connect(this, SIGNAL(playClicked()), m_trackSlider, SLOT(onTrackResumed()));
    QObject::connect(this, SIGNAL(positionChanged(qint64)), m_trackSlider, SLOT(onPositionChanged(qint64)));
    QObject::connect(this, SIGNAL(trackStarted(int)), m_trackSlider, SLOT(onTrackStarted(int)));
    QObject::connect(this, SIGNAL(trackFinished()), m_trackSlider, SLOT(onTrackFinished()));

    QObject::connect(m_backward, SIGNAL(clicked()), this, SLOT(onBackwardClicked()));
    QObject::connect(m_play, SIGNAL(clicked()), this, SLOT(onPlayClicked()));
    QObject::connect(m_pause, SIGNAL(clicked()), this, SLOT(onPauseClicked()));
    QObject::connect(m_forward, SIGNAL(clicked()), this, SLOT(onForwardClicked()));
    QObject::connect(m_trackSlider, SIGNAL(valueChanged(int)), this, SLOT(onTrackValueChanged(int)));
    QObject::connect(m_shuffle, SIGNAL(clicked()), this, SLOT(onShuffleClicked()));
    QObject::connect(m_repeat, SIGNAL(clicked()), this, SLOT(onRepeatClicked()));
    QObject::connect(m_volume, SIGNAL(clicked()), this, SLOT(onVolumeClicked()));
    QObject::connect(m_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeValueChanged(int)));

    QObject::connect(m_backward, SIGNAL(clicked()), AudioEngine::instance(), SLOT(onBackwardClicked()));
    QObject::connect(m_play, SIGNAL(clicked()), AudioEngine::instance(), SLOT(onPlayClicked()));
    QObject::connect(m_pause, SIGNAL(clicked()), AudioEngine::instance(), SLOT(onPauseClicked()));
    QObject::connect(m_forward, SIGNAL(clicked()), AudioEngine::instance(), SLOT(onForwardClicked()));
    QObject::connect(m_trackSlider, SIGNAL(valueChanged(int)), AudioEngine::instance(), SLOT(onTrackValueChanged(int)));
    QObject::connect(this, SIGNAL(volumeClicked(AudioControls::VolumeMode_t)), AudioEngine::instance(), SLOT(onVolumeClicked(AudioControls::VolumeMode_t)));
    QObject::connect(this, SIGNAL(repeatClicked(AudioControls::RepeatMode_t)), AudioEngine::instance(), SLOT(onRepeatClicked(AudioControls::RepeatMode_t)));
    QObject::connect(m_volumeSlider, SIGNAL(valueChanged(int)), AudioEngine::instance(), SLOT(onVolumeValueChanged(int)));

    QObject::connect(AudioEngine::instance(), SIGNAL(trackStarted(const Track*)), this, SLOT(onTrackStarted(const Track*)));
    QObject::connect(AudioEngine::instance(), SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    QObject::connect(AudioEngine::instance(), SIGNAL(trackFinished()), this, SLOT(onTrackFinished()));

    QObject::connect(&m_volumeShortcut, SIGNAL(activated()), this, SLOT(onVolumeClicked()));
}

AudioControls::~AudioControls()
{
}

void AudioControls::onPositionChanged(qint64 position)
{
    if(c_currentTrack)
    {
        quint16 elapsedTime = position / 1000;
        m_elapsedTime->setText(QString("%1").arg(Utils::secondsToMinutes(elapsedTime)));

        quint16 remainingTime = c_currentTrack->duration() - elapsedTime;
        m_remainingTime->setText(QString("%1").arg(Utils::secondsToMinutes(remainingTime)));
    }

    emit positionChanged(position);
}

void AudioControls::onTrackStarted(const Track* track)
{
    c_currentTrack = track;

    m_artist->show();
    m_artist->setText(c_currentTrack->artist()->name());
    m_dash->show();
    m_track->show();
    m_track->setText(c_currentTrack->title());

    m_pause->show();
    m_play->hide();

    m_elapsedTime->setText("00:00");
    m_elapsedTime->show();
    m_trackSlider->show();
    m_remainingTime->setText(Utils::secondsToMinutes(c_currentTrack->duration()));
    m_remainingTime->show();

    emit trackStarted(c_currentTrack->duration());
}

void AudioControls::onTrackFinished()
{
    c_currentTrack = NULL;

    m_artist->hide();
    m_dash->hide();
    m_track->hide();

    m_play->show();
    m_pause->hide();

    m_elapsedTime->hide();
    m_trackSlider->hide();
    m_remainingTime->hide();

    emit trackFinished();
}

void AudioControls::onBackwardClicked()
{
    emit backwardClicked();
}

void AudioControls::onPlayClicked()
{
    m_play->hide();
    m_pause->show();

    emit playClicked();
}

void AudioControls::onPauseClicked()
{
    m_pause->hide();
    m_play->show();

    emit pauseClicked();
}

void AudioControls::onForwardClicked()
{
    emit forwardClicked();
}

void AudioControls::onTrackValueChanged(int value)
{
    emit trackValueChanged(value);
}

void AudioControls::onShuffleClicked()
{
    switch (m_shuffleMode)
    {
        case AudioControls::SHUFFLE_OFF:
        {
            m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 1.0, Qt::white));
            m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 0.5, Qt::gray), QIcon::Off, QIcon::Active);
            m_shuffleMode = AudioControls::SHUFFLE_ON;
            break;
        }

        case AudioControls::SHUFFLE_ON:
        {
            m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 1.0, Qt::gray));
            m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
            m_shuffleMode = AudioControls::SHUFFLE_OFF;
            break;
        }

        default:
        {
            break;
        }
    }

    emit shuffleClicked(m_shuffleMode);
}

void AudioControls::onRepeatClicked()
{
    switch (m_repeatMode)
    {
        case AudioControls::REPEAT_NONE:
        {
            m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat-one.svg"), QSize(17, 17), 1.0, Qt::white));
            m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat-one.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
            m_repeatMode = AudioControls::REPEAT_ONE;
            break;
        }

        case AudioControls::REPEAT_ONE:
        {
            m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat-all.svg"), QSize(17, 17), 1.0, Qt::white));
            m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat-all.svg"), QSize(17, 17), 1.0, Qt::gray), QIcon::Off, QIcon::Active);
            m_repeatMode = AudioControls::REPEAT_ALL;
            break;
        }

        case AudioControls::REPEAT_ALL:
        {
            m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat.svg"), QSize(17, 17), 1.0, Qt::gray));
            m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
            m_repeatMode = AudioControls::REPEAT_NONE;
            break;
        }

        default:
        {
            break;
        }
    }

    emit repeatClicked(m_repeatMode);
}

void AudioControls::onVolumeClicked()
{
    switch (m_volumeMode)
    {
        case AudioControls::VOLUME_MUTED:
        {
            m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::white));
            m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::gray), QIcon::Off, QIcon::Active);
            m_volumeMode = AudioControls::VOLUME_NOT_MUTED;
            break;
        }

        case AudioControls::VOLUME_NOT_MUTED:
        {
            m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume-muted.svg"), QSize(17, 17), 1.0, Qt::gray));
            m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume-muted.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
            m_volumeMode = AudioControls::VOLUME_MUTED;
            break;
        }

        default:
        {
            break;
        }
    }

    emit volumeClicked(m_volumeMode);
}

void AudioControls::onVolumeValueChanged(int value)
{
    if(m_volumeMode == AudioControls::VOLUME_MUTED)
    {
        m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::white));
        m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::gray), QIcon::Off, QIcon::Active);
        m_volumeMode = AudioControls::VOLUME_NOT_MUTED;

        emit volumeClicked(m_volumeMode);
    }

    emit volumeValueChanged(value);
}
