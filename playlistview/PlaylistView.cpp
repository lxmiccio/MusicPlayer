#include "PlaylistView.h"

#include "PlaylistManager.h"

PlaylistView::PlaylistView(QWidget* parent) : QWidget(parent)
{
    m_playlist = NULL;

    m_trackInfoView = new TrackInfoView();

    m_tracksListView = new TracksListView(TracksListView::FULL, false);
    QObject::connect(m_tracksListView, SIGNAL(trackPressed(Track*)), m_trackInfoView, SLOT(changeTrack(Track*)));

    m_trackListScrollable = new ScrollableWidget();
    m_trackListScrollable->setWidget(m_tracksListView);

    m_layout = new QHBoxLayout();
    m_layout->addWidget(m_trackInfoView);
    m_layout->addWidget(m_trackListScrollable);
    m_layout->setAlignment(m_trackInfoView, Qt::AlignTop);

    setLayout(m_layout);
}

void PlaylistView::changePlaylist(const QString& name)
{
    changePlaylist(PlaylistManager::instance()->playlist(name));
}

void PlaylistView::changePlaylist(Playlist* playlist)
{
    if(playlist)
    {
        m_playlist = playlist;

        m_trackInfoView->changeTrack(m_playlist->tracks().first());

        m_tracksListView->clear();
        foreach(Track* i_track, m_playlist->tracks())
        {
            m_tracksListView->appendItem(i_track);
        }
        m_tracksListView->setMinimumHeight(m_tracksListView->fittingSize().height());
    }
}
