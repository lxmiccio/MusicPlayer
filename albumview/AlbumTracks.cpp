#include "AlbumTracks.h"

#include "AlbumCover.h"
#include "AudioEngine.h"

AlbumTracks::AlbumTracks(QWidget* parent) : QWidget(parent)
{
    m_albumCover = new AlbumCover();
    QObject::connect(m_albumCover, SIGNAL(coverClicked(Album*)), this, SIGNAL(coverClicked(Album*)));

    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->setMargin(0);
    m_leftLayout->addWidget(m_albumCover);
    m_leftLayout->addItem(m_lowerSpacer);

    m_trackView = new TrackView(PlayingView::REDUCED);
    QObject::connect(m_trackView, SIGNAL(trackDoubleClicked(Track*)), this, SLOT(onTrackSelected(Track*)));

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);
    m_layout->addLayout(m_leftLayout);
    m_layout->addWidget(m_trackView);
    setLayout(m_layout);

    QObject::connect(this, SIGNAL(playlistSelected(Playlist*)), AudioEngine::instance(), SLOT(onPlaylistSelected(Playlist*)));
}

void AlbumTracks::onAlbumSelected(Album* album)
{
    if(album)
    {
        m_album = album;

        m_albumCover->setAlbum(m_album);
        m_trackView->clear();
        foreach(Track* i_track, m_album->tracks())
        {
            m_trackView->appendItem(i_track);
        }
    }
}

void AlbumTracks::onTrackSelected(Track* track)
{
    if(track)
    {
        emit playlistSelected(Playlist::fromTracks(m_album->tracks(), track));
    }
}
