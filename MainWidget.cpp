#include "MainWidget.h"

MainWidget::MainWidget(QWidget* parent) : BackgroundWidget(parent)
{
    QImage backgroud(":/images/tove-lo.jpg");
    BackgroundWidget::setBackgroundImage(QPixmap::fromImage(ImageUtils::blur(backgroud, backgroud.rect(), 15, false, true)));

    m_artistView = new ArtistView();
    m_artistView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_albumView = new AlbumView();
    m_albumView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(m_albumView, SIGNAL(coverClicked(const Album&)), this, SLOT(onCoverClicked(const Album&)));

    if(Settings::view() == Settings::ARTIST_VIEW)
    {
        m_albumView->hide();
    }
    else
    {
        m_artistView->hide();
    }

    m_trackView = new TrackView();
    QObject::connect(m_trackView, SIGNAL(doubleClicked(const Track&)), this, SLOT(onItemDoubleClicked(const Track&)));
    QObject::connect(m_trackView, SIGNAL(coverClicked()), this, SLOT(coverClicked()));

    QObject::connect(this, SIGNAL(trackStarted(const Track&)), m_trackView, SLOT(onTrackStarted(const Track&)));

    m_audioControls = new AudioControls();
    QObject::connect(m_audioControls, SIGNAL(currentTrackClicked()), this, SLOT(onCurrentTrackClicked()));

    m_audioEngine = AudioEngine::instance();

    QObject::connect(m_audioControls, SIGNAL(backwardClicked()), m_audioEngine, SLOT(onBackwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(playClicked()), m_audioEngine, SLOT(onPlayClicked()));
    QObject::connect(m_audioControls, SIGNAL(pauseClicked()), m_audioEngine, SLOT(onPauseClicked()));
    QObject::connect(m_audioControls, SIGNAL(forwardClicked()), m_audioEngine, SLOT(onForwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(trackValueChanged(int)), m_audioEngine, SLOT(onTrackValueChanged(int)));
    QObject::connect(m_audioControls, SIGNAL(shuffleClicked(AudioControls::ShuffleMode_t)), m_audioEngine, SLOT(onShuffleClicked(AudioControls::ShuffleMode_t)));
    QObject::connect(m_audioControls, SIGNAL(repeatClicked(AudioControls::RepeatMode_t)), m_audioEngine, SLOT(onRepeatClicked(AudioControls::RepeatMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeClicked(AudioControls::VolumeMode_t)), m_audioEngine, SLOT(onVolumeClicked(AudioControls::VolumeMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeValueChanged(int)), m_audioEngine, SLOT(onVolumeValueChanged(int)));

    QObject::connect(m_audioEngine, SIGNAL(trackStarted(const Track&)), m_audioControls, SLOT(onTrackStarted(const Track&)));
    QObject::connect(m_audioEngine, SIGNAL(positionChanged(qint64)), m_audioControls, SLOT(onPositionChanged(qint64)));
    QObject::connect(m_audioEngine, SIGNAL(trackFinished()), m_audioControls, SLOT(onTrackFinished()));

    QObject::connect(m_audioEngine, SIGNAL(trackStarted(const Track&)), this, SLOT(onTrackStarted(const Track&)));
    QObject::connect(this, SIGNAL(trackClicked(const Track&)), m_audioEngine, SLOT(onTrackSelected(const Track&)));

    m_horLayout = new QHBoxLayout();
    m_horLayout->setMargin(0);
    m_horLayout->setSpacing(0);
    m_horLayout->addWidget(m_albumView);
    m_horLayout->addWidget(m_artistView);
    m_horLayout->addWidget(m_trackView);

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_trackView->hide();
    m_layout->addLayout(m_horLayout);
    m_layout->addWidget(m_audioControls);
    setLayout(m_layout);

}

MainWidget::~MainWidget()
{
}

void MainWidget::onShowArtistViewTriggered()
{
    if(m_currentView != Settings::ARTIST_VIEW)
    {
        m_currentView = Settings::ARTIST_VIEW;
        Settings::setView(m_currentView);

        m_albumView->hide();
        m_artistView->show();
    }
}

void MainWidget::onShowAlbumViewTriggered()
{
    if(m_currentView != Settings::ALBUM_VIEW)
    {
        m_currentView = Settings::ALBUM_VIEW;
        Settings::setView(m_currentView);

        m_artistView->hide();
        m_albumView->show();
    }
}

void MainWidget::onItemDoubleClicked(const Track& track)
{
    emit trackClicked(track);
}

void MainWidget::coverClicked()
{
    if(m_currentView == Settings::ARTIST_VIEW)
    {
        m_artistView->show();
    }
    else
    {
        m_albumView->show();
    }

    m_trackView->hide();
}

void MainWidget::onCoverClicked(const Album& album)
{
    m_trackView->show();
    m_trackView->onAlbumSelected(album);

    m_artistView->hide();
    m_albumView->hide();
}

void MainWidget::onCurrentTrackClicked()
{
    m_trackView->show();
    m_trackView->onPlaylistSelected(m_audioEngine->playlist());
    m_artistView->hide();
}

void MainWidget::onTrackStarted(const Track& track)
{
    emit trackStarted(track);
}
