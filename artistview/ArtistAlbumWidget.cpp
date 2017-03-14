#include "ArtistAlbumWidget.h"

#include <QApplication>
#include <QFont>

#include "AudioEngine.h"

ArtistAlbumWidget::ArtistAlbumWidget(QWidget* parent) : QWidget(parent)
{
    QFont font = QApplication::font();
    font.setBold(true);
    font.setPointSize(11);

    m_cover = new QLabel();

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_albumTitle->setContentsMargins(36, 0, 0, 0);
    m_albumTitle->setFont(font);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_model = new TrackModel();

    m_trackList = new TrackList();
    m_trackList->setModel(m_model);

    m_trackList->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_trackList->setShowGrid(false);
    m_trackList->horizontalHeader()->hide();
    m_trackList->verticalHeader()->hide();
    QObject::connect(m_trackList, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClicked(const QModelIndex&)));
    QObject::connect(this, SIGNAL(trackClicked(Track*)), AudioEngine::instance(), SLOT(onTrackSelected(Track*)));

    m_delegate = new TrackDelegate(m_trackList);
    m_trackList->setItemDelegate(m_delegate);

#if LOWER_ALIGNMENT
    m_upperLayoutLeftSpacer = new QSpacerItem(32, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_upperLayoutRightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_middleSpacer = new QSpacerItem(0, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_lowerLayoutLeftSpacer = new QSpacerItem(ArtistAlbumWidget::IMAGE_WIDTH - 6, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    m_upperLayout = new QHBoxLayout();
    m_upperLayout->setContentsMargins(0, 0, 0, 0);
    m_upperLayout->setSpacing(0);
    m_upperLayout->addWidget(m_cover);
    m_upperLayout->addItem(m_upperLayoutLeftSpacer);
    m_upperLayout->addWidget(m_albumTitle);
    m_upperLayout->addItem(m_upperLayoutRightSpacer);

    m_lowerLayout = new QHBoxLayout();
    m_lowerLayout->setContentsMargins(0, 0, 0, 0);
    m_lowerLayout->setSpacing(0);
    m_lowerLayout->addItem(m_lowerLayoutLeftSpacer);
    m_lowerLayout->addWidget(m_trackList);

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addLayout(m_upperLayout);
    m_layout->addItem(m_middleSpacer);
    m_layout->addLayout(m_lowerLayout);
    m_layout->addItem(m_lowerSpacer);
#endif

    m_leftLayoutUpperSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_leftLayoutLowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_rightLayoutMiddleSpacer = new QSpacerItem(0, 18, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    m_leftLayout->setSpacing(0);
    m_leftLayout->addItem(m_leftLayoutUpperSpacer);
    m_leftLayout->addWidget(m_cover);
    m_leftLayout->addItem(m_leftLayoutLowerSpacer);

    m_rightLayout = new QVBoxLayout();
    m_rightLayout->setContentsMargins(0, 0, 0, 0);
    m_rightLayout->setSpacing(0);
    m_rightLayout->addWidget(m_albumTitle);
    m_rightLayout->addItem(m_rightLayoutMiddleSpacer);
    m_rightLayout->addWidget(m_trackList);

    m_layout = new QHBoxLayout();
    m_layout->addLayout(m_leftLayout);
    m_layout->addLayout(m_rightLayout);

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

        QVector<Track*> tracks = m_album->tracks();

        foreach(Track* i_track, tracks)
        {
            TrackItem* item = new TrackItem(i_track);
            m_items.push_back(item);
            m_model->appendItem(i_track);
        }

        m_trackList->setMinimumHeight(m_trackList->fittingSize().height());
    }
}

void ArtistAlbumWidget::onDoubleClicked(const QModelIndex& index)
{
    Track* track = const_cast<Track*>(m_items.at(index.row())->track());
    emit trackClicked(track);
}

void ArtistAlbumWidget::clear()
{
    qDeleteAll(m_items);
    m_items.clear();

    m_model->clear();
}
