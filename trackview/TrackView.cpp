#include "TrackView.h"

#include <QHeaderView>
#include <QResizeEvent>
#include <QScrollBar>

#include "ImageUtils.h"

TrackView::TrackView(quint8 mode, QWidget* parent) : QWidget(parent)
{
    m_mode = mode;

    if(m_mode == TrackView::FULL)
    {
        m_trackAlbum = NULL;
        m_trackLyrics = NULL;
        m_leftLayout = NULL;
        m_spacer = NULL;
    }
    else
    {
        m_trackAlbum = new TrackAlbum();
        QObject::connect(m_trackAlbum, SIGNAL(coverClicked()), this, SLOT(onCoverClicked()));

        m_trackLyrics = new TrackLyrics();
        QObject::connect(this, SIGNAL(trackStarted(const Track&)), m_trackLyrics, SLOT(onTrackStarted(const Track&)));

        m_leftLayout = new QVBoxLayout();
        m_leftLayout->addWidget(m_trackAlbum);
        m_leftLayout->addWidget(m_trackLyrics);

        m_spacer = new QSpacerItem(48, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    m_trackList = new TrackList(m_mode);
    QObject::connect(m_trackList, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClicked(const QModelIndex&)));

    m_layout = new QHBoxLayout();
    m_layout->setContentsMargins(40, 16, 40, 12);
    if(m_mode == TrackView::REDUCED)
    {
        m_layout->addLayout(m_leftLayout);
        m_layout->addItem(m_spacer);
    }
    m_layout->addWidget(m_trackList);

    setLayout(m_layout);

    setMinimumHeight(TrackView::WIDGET_HEIGHT);
}

TrackView::~TrackView()
{
#if 0
    qDeleteAll(m_items);
    delete m_trackList;
    delete m_layout;
#endif
}
void TrackView::onAlbumSelected(const Album& album)
{
    clear();

    foreach(Track* i_track, album.tracks())
    {
        TrackItem* item = new TrackItem(i_track);
        m_items.push_back(item);
        m_trackList->appendItem(i_track);
    }

    m_trackAlbum->setAlbum(&album);
}

void TrackView::onPlaylistSelected(const Playlist* playlist)
{
    if(playlist && !playlist->tracks().isEmpty())
    {
        clear();

        foreach(const Track* i_track, playlist->tracks())
        {
            TrackItem* item = new TrackItem(i_track);
            m_items.push_back(item);
            m_trackList->appendItem(i_track);
        }

        m_trackAlbum->setAlbum(playlist->tracks().at(0)->album());
    }
}

void TrackView::onTrackStarted(const Track& track)
{
    m_trackAlbum->setAlbum(track.album());
    emit trackStarted(track);
}

void TrackView::onDoubleClicked(const QModelIndex& index)
{
    const Track* track = m_items.at(index.row())->track();
    emit doubleClicked(*track);
}

void TrackView::onCoverClicked()
{
    emit coverClicked();
}

void TrackView::clear()
{
    qDeleteAll(m_items);
    m_items.clear();

    m_trackList->clear();
}
