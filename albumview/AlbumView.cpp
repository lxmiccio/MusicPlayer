#include "AlbumView.h"

#include "MusicLibrary.h"

AlbumView::AlbumView(QWidget* parent) : ScrollableWidget(parent)
{
    m_albumGrid = new AlbumGrid();
    QObject::connect(m_albumGrid, SIGNAL(coverClicked(Album*)), this, SLOT(onAlbumGridCoverClicked(Album*)));

    m_albumTracks = new AlbumTracks();
    m_albumTracks->hide();
    QObject::connect(m_albumTracks, SIGNAL(coverClicked(Album*)), this, SLOT(onAlbumTracksCoverClicked(Album*)));
    QObject::connect(m_albumGrid, SIGNAL(coverClicked(Album*)), m_albumTracks, SLOT(onAlbumSelected(Album*)));

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_albumGrid);
    m_layout->addWidget(m_albumTracks);
    setLayout(m_layout);
}

AlbumView::~AlbumView()
{
}

void AlbumView::onAlbumGridCoverClicked(Album* album)
{
    if(album)
    {
        m_albumGrid->hide();
        m_albumTracks->show();
    }
}


void AlbumView::onAlbumTracksCoverClicked(Album* album)
{
    if(album)
    {
        m_albumTracks->hide();
        m_albumGrid->show();
    }
}
