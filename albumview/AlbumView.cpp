#include "AlbumView.h"

#include "MusicLibrary.h"

AlbumView::AlbumView(QWidget* parent) : ScrollableWidget(parent)
{
    m_albumGrid = new AlbumGrid();
    QObject::connect(m_albumGrid, SIGNAL(coverClicked(Album*)), this, SLOT(onAlbumGridCoverClicked(Album*)));

    m_albumInfo = new AlbumInfoView();
    m_albumInfo->hide();
    m_albumTracks = new AlbumTracks();
    m_albumTracks->hide();
    QObject::connect(m_albumInfo, SIGNAL(coverClicked(Album*)), this, SLOT(onAlbumTracksCoverClicked(Album*)));
    QObject::connect(m_albumGrid, SIGNAL(coverClicked(Album*)), m_albumInfo, SLOT(changeAlbum(Album*)));

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_albumGrid);
    m_layout->addWidget(m_albumInfo);
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
        m_albumInfo->show();
    }
}


void AlbumView::onAlbumTracksCoverClicked(Album* album)
{
    if(album)
    {
        m_albumInfo->hide();
        m_albumGrid->show();
    }
}
