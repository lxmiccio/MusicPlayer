#include "PlayingView.h"

#include "AudioEngine.h"

PlayingView::PlayingView(quint8 mode, QWidget* parent) : QWidget(parent)
{
    m_mode = mode;

    if(m_mode == PlayingView::FULL)
    {
        m_playingAlbum = NULL;
        m_playingLyrics = NULL;
        m_leftLayout = NULL;
        m_spacer = NULL;

        m_scrollableArea = new ScrollableArea();
    }
    else
    {
        m_playingAlbum = new PlayingAlbum();
        QObject::connect(m_playingAlbum, SIGNAL(leftButtonClicked()), this, SLOT(onCoverClicked()));

        m_playingLyrics = new PlayingLyrics();

        m_leftLayout = new QVBoxLayout();
        m_leftLayout->setMargin(0);
        m_leftLayout->addWidget(m_playingAlbum);
        m_leftLayout->addWidget(m_playingLyrics);

        m_spacer = new QSpacerItem(48, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

        m_scrollableArea = NULL;
    }

    m_trackView = new TrackView(m_mode);
    QObject::connect(m_trackView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClicked(const QModelIndex&)));

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);

    if(m_mode == PlayingView::FULL)
    {
        m_scrollableArea->setWidget(m_trackView);
        m_layout->addWidget(m_trackView);
    }
    else
    {
        m_layout->addLayout(m_leftLayout);
        m_layout->addItem(m_spacer);
        m_layout->addWidget(m_trackView);
    }

    setMinimumHeight(PlayingView::WIDGET_HEIGHT);
    setLayout(m_layout);
}

PlayingView::~PlayingView()
{
#if 0
    qDeleteAll(m_items);
    delete m_trackView;
    delete m_layout;
#endif
}

void PlayingView::onAlbumSelected(const Album* album)
{
    if(album)
    {
        clear();

        foreach(Track* i_track, album->tracks())
        {
            TrackItem* item = new TrackItem(i_track);
            m_items.push_back(item);
            m_trackView->appendItem(i_track);
        }

        m_playingAlbum->setAlbum(album);
    }
}

void PlayingView::onPlaylistSelected(const Playlist* playlist)
{
    if(playlist && !playlist->tracks().isEmpty())
    {
        clear();

        foreach(const Track* i_track, playlist->tracks())
        {
            TrackItem* item = new TrackItem(i_track);
            m_items.push_back(item);
            m_trackView->appendItem(i_track);
        }

        m_playingAlbum->setAlbum(playlist->tracks().at(0)->album());
    }
}

void PlayingView::onDoubleClicked(const QModelIndex& index)
{
    const Track* track = m_items.at(index.row())->track();

    if(track && track->album())
    {
        Playlist* playlist = Playlist::fromTracks(track->album()->tracks(), track);
        AudioEngine::instance()->onPlaylistSelected(playlist);
    }
}

void PlayingView::onCoverClicked()
{
    emit coverClicked();
}

void PlayingView::clear()
{
    qDeleteAll(m_items);
    m_items.clear();

    m_trackView->clear();
}
