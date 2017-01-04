#include "AudioControls.h"

#include <QApplication>

#include "ImageUtils.h"

AudioControls::AudioControls(QWidget* parent) : QWidget(parent)
{
    QFont font = QApplication::font();
    font.setPointSize(13);

    m_upperSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding);

    m_artist = new QLabel("WTF Love Is");
    m_artist->setFont(font);
    m_artist->setStyleSheet(QString("color: white;"));

    m_dash = new QLabel("-");
    m_dash->setFont(font);
    m_dash->setStyleSheet(QString("color: white;"));

    m_track = new QLabel("Tove Lo");
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
    QObject::connect(m_backward, SIGNAL(clicked()), this, SLOT(onBackwardClicked()));

    m_lowerSpacer1 = new QSpacerItem(16, 0, QSizePolicy::Fixed);

    m_play = new ImageButton();
    m_play->setPixmap(ImageUtils::pixmap(QString(":/svg/play.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_play->setPixmap(ImageUtils::pixmap(QString(":/svg/play.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
    QObject::connect(m_play, SIGNAL(clicked()), this, SLOT(onPlayClicked()));

    m_pause = new ImageButton();
    m_pause->setPixmap(ImageUtils::pixmap(QString(":/svg/pause.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_pause->setPixmap(ImageUtils::pixmap(QString(":/svg/pause.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
    m_pause->hide();
    QObject::connect(m_pause, SIGNAL(clicked()), this, SLOT(onPauseClicked()));

    m_lowerSpacer2 = new QSpacerItem(16, 0, QSizePolicy::Fixed);

    m_forward = new ImageButton();
    m_forward->setPixmap(ImageUtils::pixmap(QString(":/svg/forward.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_forward->setPixmap(ImageUtils::pixmap(QString(":/svg/forward.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
    QObject::connect(m_forward, SIGNAL(clicked()), this, SLOT(onForwardClicked()));

    m_lowerSpacer3 = new QSpacerItem(204, 0, QSizePolicy::Fixed);

    font.setPointSize(9);

    m_elapsedTime = new QLabel("00:00");
    m_elapsedTime->setFont(font);
    m_elapsedTime->setStyleSheet(QString("color: white; margin-top: -2px;"));

    m_lowerSpacer4 = new QSpacerItem(6, 0, QSizePolicy::Fixed);

    m_musicTimeline = new QTimeLine();

    m_musicSlider = new SeekSlider(Qt::Horizontal);
    m_musicSlider->setTimeLine(m_musicTimeline);
    m_musicSlider->setFixedHeight(6);
    m_musicSlider->setMinimumWidth(256);
    m_musicSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    QObject::connect(m_musicSlider, SIGNAL(sliderMoved(int)), this, SLOT(onMusicSliderMoved(int)));
    QObject::connect(m_musicSlider, SIGNAL(sliderPressed()), this, SLOT(onMusicSliderMoved(int)));
    QObject::connect(m_musicSlider, SIGNAL(sliderReleased()), this, SLOT(onMusicSliderMoved(int)));
    QObject::connect(m_musicSlider, SIGNAL(), this, SLOT(onMusicSliderMoved(int)));

    QObject::connect(m_musicTimeline, SIGNAL(frameChanged(int)), m_musicSlider, SLOT(setValue(int)));

    m_lowerSpacer5 = new QSpacerItem(6, 0, QSizePolicy::Fixed);

    m_remainingTime = new QLabel("00:00");
    m_remainingTime->setFont(font);
    m_remainingTime->setStyleSheet(QString("color: white; margin-top: -2px;"));

    m_lowerSpacer6 = new QSpacerItem(36, 0, QSizePolicy::Fixed);

    m_shuffle = new ImageButton();
    m_shuffle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_shuffle->setPixmap(ImageUtils::pixmap(QString(":/svg/shuffle.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
    QObject::connect(m_shuffle, SIGNAL(clicked()), this, SLOT(onShuffleClicked()));

    m_lowerSpacer7 = new QSpacerItem(36, 0, QSizePolicy::Fixed);

    m_repeat = new ImageButton();
    m_repeat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat.svg"), QSize(17, 17), 1.0, Qt::gray));
    m_repeat->setPixmap(ImageUtils::pixmap(QString(":/svg/repeat.svg"), QSize(17, 17), 1.0, Qt::white), QIcon::Off, QIcon::Active);
    QObject::connect(m_repeat, SIGNAL(clicked()), this, SLOT(onRepeatClicked()));

    m_lowerSpacer8 = new QSpacerItem(36, 0, QSizePolicy::Fixed);

    m_volume = new ImageButton();
    m_volume->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::white));
    m_volume->setPixmap(ImageUtils::pixmap(QString(":/svg/volume.svg"), QSize(17, 17), 1.0, Qt::gray), QIcon::Off, QIcon::Active);
    QObject::connect(m_volume, SIGNAL(clicked()), this, SLOT(onVolumeClicked()));

    m_volumeSlider = new SeekSlider(Qt::Horizontal);
    m_volumeSlider->setAcceptWheelEvents(true);
    m_volumeSlider->setLockScubbing(false);
    m_volumeSlider->setFixedHeight(6);
    m_volumeSlider->setMinimumWidth(120);
    m_volumeSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(m_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeValueChanged(int)));

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
    m_lowerHorizontalLayout->addWidget(m_musicSlider);
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

    m_repeatMode = AudioControls::REPEAT_NONE;
    m_shuffleMode = AudioControls::SHUFFLE_OFF;
    m_volumeMode = AudioControls::VOLUME_NOT_MUTED;
}

AudioControls::~AudioControls()
{
#if 0
    delete m_upperSpacer1;
    delete m_artist;
    delete m_dash;
    delete m_track;
    delete m_upperSpacer2;
    delete m_upperHorizontalLayout;

    delete m_lowerSpacer1;
    delete m_backward;
    delete m_lowerSpacer2;
    delete m_play;
    delete m_pause;
    delete m_lowerSpacer3;
    delete m_forward;
    delete m_lowerSpacer4;
    delete m_elapsedTime;
    delete m_lowerSpacer5;
    delete m_musicSlider;
    delete m_lowerSpacer6;
    delete m_remainingTime;
    delete m_lowerSpacer7;
    delete m_shuffle;
    delete m_lowerSpacer8;
    delete m_repeat;
    delete m_lowerSpacer9;
    delete m_volume;
    delete m_volumeSlider;
    delete m_lowerSpacer10;
    delete m_lowerHorizontalLayout;

    delete m_verticalLayout;
#endif
}

void AudioControls::showPlay(bool show)
{
    show ? m_play->show() : m_play->hide();
}

void AudioControls::showPause(bool show)
{
    show ? m_pause->show() : m_pause->hide();
}

void AudioControls::onTrackStarted(const Track& track)
{
    m_artist->show();
    m_dash->show();
    m_track->show();

    m_artist->setText(track.artist()->name());
    m_track->setText(track.title());

    m_musicTimeline->setCurrentTime(0);
    m_musicTimeline->setCurveShape(QTimeLine::LinearCurve);
    m_musicTimeline->setDuration(track.duration());
    m_musicTimeline->setFrameRange(0, track.duration());
    m_musicTimeline->setUpdateInterval(10000);
    m_musicTimeline->start();
}

void AudioControls::onPlaylistEnded()
{
    m_artist->hide();
    m_dash->hide();
    m_track->hide();
}

void AudioControls::onPositionChanged(qint64 position, qint64 duration)
{
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

void AudioControls::onMusicSliderMoved(int position)
{
    emit musicSliderMoved(position, m_musicSlider->minimum(), m_musicSlider->maximum());
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

void AudioControls::onVolumeValueChanged(int position)
{
    emit volumeValueChanged(position);
}
