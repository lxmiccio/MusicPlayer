#include "ArtistAlbumWidget.h"

ArtistAlbumWidget::ArtistAlbumWidget(QWidget* parent) : QWidget(parent)
{
    m_cover = new QLabel();
    m_albumTitle = new ElidedLabel();

    m_model = new TrackModel();

    m_trackList = new TrackList();
    m_trackList->setModel(m_model);

    m_trackList->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_trackList->setShowGrid(false);
    m_trackList->horizontalHeader()->hide();
    m_trackList->verticalHeader()->hide();
    // QObject::connect(m_trackList, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClicked(const QModelIndex&)));

    m_delegate = new TrackDelegate(m_trackList);
    m_trackList->setItemDelegate(m_delegate);

    m_upperLayout = new QHBoxLayout();
    m_upperLayout->addWidget(m_cover);
    m_upperLayout->addWidget(m_albumTitle);

    m_layout = new QVBoxLayout();
    m_layout->addLayout(m_upperLayout);
    m_layout->addWidget(m_trackList);

    setLayout(m_layout);
}

void ArtistAlbumWidget::setAlbum(Album* album)
{
    if(album)
    {
        m_album = album;

        clear();

        if(m_album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(m_album->cover().scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }

        m_albumTitle->setText(m_album->title());

        foreach(Track* i_track, album->tracks())
        {
            TrackItem* item = new TrackItem(i_track);
            m_items.push_back(item);
            m_model->appendItem(i_track);
        }
    }
}

void ArtistAlbumWidget::clear()
{
    qDeleteAll(m_items);
    m_items.clear();

    m_model->clear();
}
