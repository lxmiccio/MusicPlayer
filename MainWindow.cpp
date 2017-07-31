#include "MainWindow.h"

#include "MainWidget.h"
#include "PlaylistManager.h"

MainWindow* MainWindow::m_instance = NULL;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    MainWidget* mainWidget = MainWidget::instance(this);
    setCentralWidget(mainWidget);

    m_showArtistView = new QAction("ArtistView");
    m_showAlbumView = new QAction("AlbumView");
    m_showTrackView = new QAction("TrackView");

    m_playlistMenu = new QMenu("Playlists");

    for(quint16 i = 0; i < PlaylistManager::instance()->playlistsName().size(); ++i)
    {
        m_playlistsView.push_back(new QAction(PlaylistManager::instance()->playlistsName().at(i)));
        m_playlistMenu->addAction(m_playlistsView.last());

        QObject::connect(m_playlistsView.last(), SIGNAL(triggered(bool)), mainWidget, SLOT(onShowPlaylistViewTriggered()));
    }

    QObject::connect(PlaylistManager::instance(), SIGNAL(playlistsChanged()), SLOT(onPlaylistsChanged()));

    m_viewsMenu = new QMenu("Views");
    m_viewsMenu->addAction(m_showArtistView);
    m_viewsMenu->addAction(m_showAlbumView);
    m_viewsMenu->addAction(m_showTrackView);
    m_viewsMenu->addMenu(m_playlistMenu);

    m_menuBar = new QMenuBar(this);
    m_menuBar->addMenu(m_viewsMenu);
    setMenuBar(m_menuBar);
    QObject::connect(m_showArtistView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowArtistViewTriggered()));
    QObject::connect(m_showAlbumView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowAlbumViewTriggered()));
    QObject::connect(m_showTrackView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowTrackViewTriggered()));
}

MainWindow* MainWindow::instance()
{
    if(!m_instance)
    {
        m_instance = new MainWindow();
    }

    return m_instance;
}

void MainWindow::onPlaylistsChanged()
{
    while(!m_playlistsView.isEmpty())
    {
        QAction* action = m_playlistsView.takeFirst();
        QObject::disconnect(action, SIGNAL(triggered(bool)), MainWidget::instance(this), SLOT(onShowPlaylistViewTriggered()));

        m_playlistMenu->removeAction(action);
    }

    for(quint16 i = 0; i < PlaylistManager::instance()->playlistsName().size(); ++i)
    {
        m_playlistsView.push_back(new QAction(PlaylistManager::instance()->playlistsName().at(i)));
        m_playlistMenu->addAction(m_playlistsView.last());

        QObject::connect(m_playlistsView.last(), SIGNAL(triggered(bool)), MainWidget::instance(this), SLOT(onShowPlaylistViewTriggered()));
    }
}
