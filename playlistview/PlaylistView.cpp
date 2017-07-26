#include "PlaylistView.h"

PlaylistView::PlaylistView(QWidget* parent) : QWidget(parent)
{
    m_playlist = NULL;

    m_trackInfoView = new TrackInfoView();

    m_tracksListView = new TracksListView(TracksListView::FULL);
    QObject::connect(m_tracksListView, SIGNAL(trackDoubleClicked(Track*)), m_trackInfoView, SLOT(changeTrack(Track*)));

    m_layout = new QHBoxLayout();
    m_layout->addWidget(m_trackInfoView);
    m_layout->addWidget(m_tracksListView);

    setLayout(m_layout);
}

void PlaylistView::changePlaylist(Playlist* playlist)
{
    if(playlist)
    {
        m_playlist = playlist;

        foreach(Track* i_track, m_playlist->tracks())
        {
            qDebug() << i_track->title();
            m_tracksListView->appendItem(i_track);
        }
        m_tracksListView->setMinimumHeight(m_tracksListView->fittingSize().height());
    }
}
