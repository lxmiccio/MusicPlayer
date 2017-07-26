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

    m_tracksListView = new TracksListView(TracksListView::FULL);
    QObject::connect(m_tracksListView, SIGNAL(trackDoubleClicked(Track*)), this, SLOT(onTrackDoubleClicked(Track*)));
    QObject::connect(MusicLibrary::instance(), SIGNAL(trackAdded(Track*)), m_tracksListView, SLOT(appendItem(Track*)));

    m_playingView = new PlayingView(TracksListView::REDUCED);
    QObject::connect(m_playingView, SIGNAL(doubleClicked(Track*)), this, SLOT(onTrackDoubleClicked(Track*)));
    QObject::connect(m_playingView, SIGNAL(coverClicked()), this, SLOT(coverClicked()));

    m_playlistView = new PlaylistView();

    m_currentView = Settings::NO_VIEW;
    showView(Settings::view());

    m_audioControls = new AudioControls();
    QObject::connect(m_audioControls, SIGNAL(currentTrackClicked()), this, SLOT(onCurrentTrackClicked()));

    m_audioEngine = AudioEngine::instance();


    QObject::connect(m_audioEngine, SIGNAL(trackStarted(Track*)), this, SLOT(onTrackStarted(Track*)));

    m_horLayout = new QHBoxLayout();
    m_horLayout->setMargin(0);
    m_horLayout->setSpacing(0);
    m_horLayout->addWidget(m_albumView);
    m_horLayout->addWidget(m_artistView);
    m_horLayout->addWidget(m_tracksListView);
    m_horLayout->addWidget(m_playlistView);
    m_horLayout->addWidget(m_playingView);

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(32, 16, 32, 16);
    m_layout->setSpacing(0);
    m_layout->addLayout(m_horLayout);
    m_layout->addWidget(m_audioControls);
    setLayout(m_layout);

    /* Load playlists */
    PlaylistManager::instance();
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

void MainWidget::onShowPlaylistViewTriggered()
{
    showView(Settings::PLAYLIST_VIEW);
}

void MainWidget::coverClicked()
{
    showView(Settings::view());
}

void MainWidget::onCoverClicked(Album* album)
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

void MainWidget::onTrackStarted(Track* track)
{
    if(track)
    {
        emit trackStarted(track);
    }
}

void MainWidget::showView(Settings::View view)
{
    if(view != m_currentView && view != Settings::NO_VIEW)
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
        m_tracksListView->hide();
        m_playlistView->hide();
        m_playingView->hide();

        if(m_currentView == Settings::ARTIST_VIEW) m_artistView->show();
        else if(m_currentView == Settings::ALBUM_VIEW) m_albumView->show();
        else if(m_currentView == Settings::TRACK_VIEW) m_tracksListView->show();
        else if(m_currentView == Settings::PLAYLIST_VIEW) { m_playlistView->show(); m_playlistView->changePlaylist(PlaylistManager::instance()->playlists().at(0)); }
        else if(m_currentView == Settings::PLAYING_VIEW) m_playingView->show();
    }
}

void MainWidget::onTrackDoubleClicked(Track* track)
{
    Playlist* playlist = Playlist::fromTracks(MusicLibrary::instance()->tracks(), track);
    AudioEngine::instance()->onPlaylistSelected(playlist);
}
