#include "TrackView.h"

#include <QHeaderView>
#include <QResizeEvent>
#include <QScrollBar>

#include "ImageUtils.h"

TrackView::TrackView(QWidget* parent) : QWidget(parent)
{
    m_trackAlbum = new TrackAlbum();
    QObject::connect(m_trackAlbum, SIGNAL(coverClicked()), this, SLOT(onCoverClicked()));

    m_spacer = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_model = new TrackModel();

    m_trackList = new TrackList();
    m_trackList->setModel(m_model);

    m_trackList->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_trackList->setShowGrid(false);
    m_trackList->horizontalHeader()->hide();
    m_trackList->verticalHeader()->hide();
    QObject::connect(m_trackList, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClicked(const QModelIndex&)));

    m_layout = new QHBoxLayout();
    m_layout->setContentsMargins(40, 16, 40, 12);
    m_layout->addWidget(m_trackAlbum);
    m_layout->addItem(m_spacer);
    m_layout->addWidget(m_trackList);

    m_delegate = new TrackDelegate(m_trackList);
    m_trackList->setItemDelegate(m_delegate);

    m_items = QVector<TrackItem*>();

    setLayout(m_layout);

    setMinimumHeight(TrackView::WIDGET_HEIGHT);
}

TrackView::~TrackView()
{
#if 0
    qDeleteAll(m_items);
    delete m_model;
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
        m_model->appendItem(i_track);
    }

    m_trackAlbum->setAlbum(&album);
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

    m_model->clear();
}
