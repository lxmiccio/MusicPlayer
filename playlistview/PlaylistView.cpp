#include "PlaylistView.h"

#include <QInputDialog>

#include "MainWidget.h"
#include "PlaylistManager.h"

PlaylistView::PlaylistView(QWidget* parent) : QWidget(parent)
{
    m_playlist = NULL;

    m_trackInfoView = new TrackInfoView();

    m_tracksListView = new TracksListView(TracksListView::FULL, false);
    QObject::connect(m_tracksListView, SIGNAL(trackSelected(Track*)), m_trackInfoView, SLOT(changeTrack(Track*)));
    QObject::connect(m_tracksListView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onContextMenuRequested(QPoint)));
    QObject::disconnect(m_tracksListView, SIGNAL(customContextMenuRequested(QPoint)), m_tracksListView, SLOT(onContextMenuRequested(QPoint)));

    m_trackListScrollable = new ScrollableWidget();
    m_trackListScrollable->setWidget(m_tracksListView);

    m_layout = new QHBoxLayout();
    m_layout->addWidget(m_trackInfoView);
    m_layout->addWidget(m_trackListScrollable);
    m_layout->setAlignment(m_trackInfoView, Qt::AlignTop);
    m_layout->setMargin(0);
    m_layout->setSpacing(32);

    setLayout(m_layout);
}

void PlaylistView::changePlaylist(const QString& name)
{
    changePlaylist(PlaylistManager::instance()->playlist(name));
}

void PlaylistView::changePlaylist(Playlist* playlist)
{
    if(playlist && !playlist->tracks().isEmpty())
    {
        if(m_playlist)
        {
            QObject::disconnect(m_playlist, SIGNAL(playlistUpdated()), this, SLOT(onPlaylistUpdated()));
        }

        m_playlist = playlist;
        QObject::connect(m_playlist, SIGNAL(playlistUpdated()), SLOT(onPlaylistUpdated()));

        m_trackInfoView->changeTrack(m_playlist->tracks().first());

        m_tracksListView->clear();
        foreach(Track* i_track, m_playlist->tracks())
        {
            m_tracksListView->appendItem(i_track);
        }
    }
}

void PlaylistView::onContextMenuRequested(QPoint position)
{
    QMenu menu(this);

    QAction* removeTrack = menu.addAction("Remove track");
    menu.addSeparator();

    QMenu playlistMenu("Add to playlist");
    QAction* addPlaylist = playlistMenu.addAction("Create new");
    playlistMenu.addSeparator();

    QVector<QAction*> playlists;
    QStringList playlistsName = PlaylistManager::instance()->playlistsName();
    for(quint16 i = 0; i < playlistsName.size(); ++i)
    {
        playlists.append(playlistMenu.addAction(playlistsName.at(i)));
    }

    menu.addMenu(&playlistMenu);

    QAction* selectedAction = menu.exec(m_tracksListView->viewport()->mapToGlobal(position));
    if(selectedAction == removeTrack)
    {
        QModelIndexList selection = m_tracksListView->selectionModel()->selectedRows();
        while(!selection.isEmpty())
        {
            m_playlist->removeTrack(static_cast<TracksListModel*>(m_tracksListView->model())->rootItem()->child(selection.takeLast().row())->track());
        }
    }
    else if(selectedAction == addPlaylist)
    {
        QString newPlaylist = QInputDialog::getText(0, "Create playlist", "Title:");

        Playlist* playlist = PlaylistManager::instance()->playlist(newPlaylist);
        if(!playlist)
        {
            playlist = new Playlist(newPlaylist);
        }

        QModelIndexList selection = m_tracksListView->selectionModel()->selectedRows();
        for(quint16 i = 0; i < selection.size(); ++i)
        {
            playlist->addTrack(static_cast<TracksListModel*>(m_tracksListView->model())->rootItem()->child(selection.at(i).row())->track());
        }

        PlaylistManager::instance()->savePlaylist(playlist);
    }
    else if(playlists.contains(selectedAction))
    {
        Playlist* playlist = PlaylistManager::instance()->playlist(playlists.at(playlists.indexOf(selectedAction))->text());
        if(playlist)
        {
            QModelIndexList selection = m_tracksListView->selectionModel()->selectedRows();
            for(quint16 i = 0; i < selection.size(); ++i)
            {
                playlist->addTrack(static_cast<TracksListModel*>(m_tracksListView->model())->rootItem()->child(selection.at(i).row())->track());
            }
        }

        PlaylistManager::instance()->savePlaylist(playlist);
    }
}

void PlaylistView::onPlaylistUpdated()
{
    if(!m_playlist->tracks().isEmpty())
    {
        m_trackInfoView->changeTrack(m_playlist->tracks().first());

        m_tracksListView->clear();
        foreach(Track* i_track, m_playlist->tracks())
        {
            m_tracksListView->appendItem(i_track);
        }
    }
    else
    {
        m_tracksListView->clear();

        MainWidget::instance()->showPreviousView();
    }
}
