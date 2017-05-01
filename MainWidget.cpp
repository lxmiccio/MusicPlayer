#include "MainWidget.h"

#include "Playlist.h"

MainWidget::MainWidget(QWidget* parent) : BackgroundWidget(parent)
{
    QImage backgroud(":/images/tove-lo.jpg");
    BackgroundWidget::setBackgroundImage(QPixmap::fromImage(ImageUtils::blur(backgroud, backgroud.rect(), 15, false, true)));

    m_artistView = new ArtistView();
    m_artistView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_albumView = new AlbumView();
    m_albumView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(m_albumView, SIGNAL(coverClicked(const Album*)), this, SLOT(onCoverClicked(const Album*)));

    m_trackView = new TrackView(PlayingView::FULL);
    QObject::connect(m_trackView, SIGNAL(trackDoubleClicked(const Track*)), this, SLOT(onTrackDoubleClicked(const Track*)));
    QObject::connect(MusicLibrary::instance(), SIGNAL(trackAdded(const Track*)), m_trackView, SLOT(appendItem(const Track*)));

    m_playingView = new PlayingView(PlayingView::REDUCED);
    QObject::connect(m_playingView, SIGNAL(doubleClicked(const Track*)), this, SLOT(onTrackDoubleClicked(const Track*)));
    QObject::connect(m_playingView, SIGNAL(coverClicked()), this, SLOT(coverClicked()));

    showView(Settings::view());

    m_audioControls = new AudioControls();
    QObject::connect(m_audioControls, SIGNAL(currentTrackClicked()), this, SLOT(onCurrentTrackClicked()));

    m_audioEngine = AudioEngine::instance();


    QObject::connect(m_audioEngine, SIGNAL(trackStarted(const Track*)), this, SLOT(onTrackStarted(const Track*)));

    m_horLayout = new QHBoxLayout();
    m_horLayout->setMargin(0);
    m_horLayout->setSpacing(0);
    m_horLayout->addWidget(m_albumView);
    m_horLayout->addWidget(m_artistView);
    m_horLayout->addWidget(m_trackView);
    m_horLayout->addWidget(m_playingView);

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(32, 16, 32, 16);
    m_layout->setSpacing(0);
    m_layout->addLayout(m_horLayout);
    m_layout->addWidget(m_audioControls);
    setLayout(m_layout);
}

MainWidget::~MainWidget()
{
}

void MainWidget::onShowArtistViewTriggered()
{
    showView(Settings::ARTIST_VIEW);
}

void MainWidget::onShowAlbumViewTriggered()
{
    showView(Settings::ALBUM_VIEW);
}

void MainWidget::onShowTrackViewTriggered()
{
    showView(Settings::TRACK_VIEW);
}

void MainWidget::coverClicked()
{
    showView(Settings::view());
}

void MainWidget::onCoverClicked(const Album* album)
{
    /* TODO: Move to AlbumView */
    /*
    if(album)
    {
        m_playingView->onAlbumSelected(album);
        showView(Settings::PLAYING_VIEW);
    }
    */
}

void MainWidget::onCurrentTrackClicked()
{
    m_playingView->onPlaylistSelected(m_audioEngine->playlist());
    showView(Settings::PLAYING_VIEW);
}

void MainWidget::onTrackStarted(const Track* track)
{
    if(track)
    {
        emit trackStarted(track);
    }
}

void MainWidget::showView(Settings::View view)
{
    if(view != m_currentView)
    {
        if(view == Settings::PLAYING_VIEW && m_currentView != Settings::PLAYING_VIEW)
        {
            m_previousView = m_currentView;
        }

        m_currentView = view;

        if(m_currentView != Settings::PLAYING_VIEW)
        {
            Settings::setView(m_currentView);
        }

        m_artistView->hide();
        m_albumView->hide();
        m_trackView->hide();
        m_playingView->hide();

        if(m_currentView == Settings::ARTIST_VIEW) m_artistView->show();
        else if(m_currentView == Settings::ALBUM_VIEW) m_albumView->show();
        else if(m_currentView == Settings::TRACK_VIEW) m_trackView->show();
        else if(m_currentView == Settings::PLAYING_VIEW) m_playingView->show();
    }
}

void MainWidget::onTrackDoubleClicked(const Track* track)
{
    Playlist* playlist = Playlist::fromTracks(MusicLibrary::instance()->tracks(), track);
    AudioEngine::instance()->onPlaylistSelected(playlist);
}
