#include "MainWindow.h"

#include "MainWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_stackedWidget = new QStackedWidget();
    setCentralWidget(m_stackedWidget);

    m_showArtistView = new QAction("ArtistView");
    m_showAlbumView = new QAction("AlbumView");
    m_showTrackView = new QAction("TrackView");
    m_showPlaylistView = new QAction("PlaylistView");

    m_viewsMenu = new QMenu("Views");
    m_viewsMenu->addAction(m_showArtistView);
    m_viewsMenu->addAction(m_showAlbumView);
    m_viewsMenu->addAction(m_showTrackView);
    m_viewsMenu->addAction(m_showPlaylistView);

    m_menuBar = new QMenuBar(this);
    m_menuBar->addMenu(m_viewsMenu);
    setMenuBar(m_menuBar);

    MainWidget* mainWidget = new MainWidget(this);
    m_stackedWidget->addWidget(mainWidget);
    QObject::connect(m_showArtistView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowArtistViewTriggered()));
    QObject::connect(m_showAlbumView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowAlbumViewTriggered()));
    QObject::connect(m_showTrackView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowTrackViewTriggered()));
    QObject::connect(m_showPlaylistView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowPlaylistViewTriggered()));
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
