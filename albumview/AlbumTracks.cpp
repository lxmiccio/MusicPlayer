#include "AlbumTracks.h"

AlbumTracks::AlbumTracks(QWidget* parent) : QWidget(parent)
{
    m_albumCover = new AlbumCover();
    QObject::connect(m_albumCover, SIGNAL(coverClicked(Album*)), this, SIGNAL(coverClicked(Album*)));

    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->setMargin(0);
    m_leftLayout->addWidget(m_albumCover);
    m_leftLayout->addItem(m_lowerSpacer);

    m_tracksListView = new TracksListView(TracksListView::REDUCED);

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);
    m_layout->addLayout(m_leftLayout);
    m_layout->addWidget(m_tracksListView);
    setLayout(m_layout);
}

void AlbumTracks::onAlbumSelected(Album* album)
{
    if(album)
    {
        m_album = album;

        m_albumCover->setAlbum(m_album);
        m_tracksListView->clear();

        foreach(Track* i_track, m_album->tracks())
        {
            m_tracksListView->appendItem(i_track);
        }
    }
}
