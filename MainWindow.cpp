#include "MainWindow.h"

#include "MainWidget.h"
#include "PlaylistManager.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_stackedWidget = new QStackedWidget();
    setCentralWidget(m_stackedWidget);

    MainWidget* mainWidget = new MainWidget(this);
    m_stackedWidget->addWidget(mainWidget);

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

QStackedWidget* MainWindow::stackedWidget()
{
    return m_stackedWidget;
}

void MainWindow::previousView()
{
    QString currentClassName = m_stackedWidget->currentWidget()->metaObject()->className();

    for(qint8 i = m_stackedWidget->count() - 1; i >= 0; --i)
    {
        QWidget* widget = m_stackedWidget->widget(i);

        if(widget->metaObject()->className() == currentClassName)
        {
            m_stackedWidget->removeWidget(widget);
            delete widget;
        }
        else
        {
            m_stackedWidget->setCurrentWidget(m_stackedWidget->widget(i));
            break;
        }
    }
}
