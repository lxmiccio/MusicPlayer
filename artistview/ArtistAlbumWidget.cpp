#include "ArtistAlbumWidget.h"

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

    m_trackView = new TrackView(PlayingView::REDUCED);
    QObject::connect(m_trackView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClicked(const QModelIndex&)));
    QObject::connect(this, SIGNAL(playlistSelected(Playlist*)), AudioEngine::instance(), SLOT(onPlaylistSelected(Playlist*)));

    m_leftLayoutUpperSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_leftLayoutMiddleSpacer = new QSpacerItem(0, 18, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_leftLayoutLowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_rightLayoutMiddleSpacer = new QSpacerItem(0, 18, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    m_leftLayout->setSpacing(0);
    m_leftLayout->addItem(m_leftLayoutUpperSpacer);
    m_leftLayout->addWidget(m_cover);
    m_leftLayout->addItem(m_leftLayoutMiddleSpacer);
    m_leftLayout->addItem(m_leftLayoutLowerSpacer);

    m_rightLayout = new QVBoxLayout();
    m_rightLayout->setContentsMargins(0, 0, 0, 0);
    m_rightLayout->setSpacing(0);
    m_rightLayout->addWidget(m_albumTitle);
    m_rightLayout->addItem(m_rightLayoutMiddleSpacer);
    m_rightLayout->addWidget(m_trackView);

    m_layout = new QHBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addLayout(m_leftLayout);
    m_layout->addLayout(m_rightLayout);

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
    m_lowerLayout->addWidget(m_trackView);

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addLayout(m_upperLayout);
    m_layout->addItem(m_middleSpacer);
    m_layout->addLayout(m_lowerLayout);
    m_layout->addItem(m_lowerSpacer);
#endif

    setLayout(m_layout);
}

ArtistAlbumWidget::~ArtistAlbumWidget()
{
    //TODO
}

Album* ArtistAlbumWidget::album() const
{
    return m_album;
}

void ArtistAlbumWidget::setAlbum(Album* album, quint8 fields)
{
    if(album)
    {
        m_album = album;
        QObject::connect(m_album, SIGNAL(albumUpdated(Album*, quint8)), this, SLOT(onAlbumUpdated(Album*, quint8)));

        m_albumTitle->setText(m_album->title());

        if(m_album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(ArtistAlbumWidget::IMAGE_WIDTH,
                                                                                                   ArtistAlbumWidget::IMAGE_HEIGHT,
                                                                                                   Qt::KeepAspectRatio,
                                                                                                   Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(m_album->cover().scaled(ArtistAlbumWidget::IMAGE_WIDTH,
                                                               ArtistAlbumWidget::IMAGE_HEIGHT,
                                                               Qt::KeepAspectRatio,
                                                               Qt::SmoothTransformation)));
        }

        foreach(Track* i_track, m_album->tracks())
        {
            m_trackView->appendItem(i_track);
        }
        m_trackView->setMinimumHeight(m_trackView->fittingSize().height());
    }
}

void ArtistAlbumWidget::onAlbumUpdated(Album* album, quint8 fields)
{
    if(album && album == m_album)
    {
        setAlbum(album);
    }
}

void ArtistAlbumWidget::onDoubleClicked(const QModelIndex& index)
{
    const Track* track = m_trackView->trackModel()->rootItem()->child(index.row())->track();

    if(track)
    {
        emit playlistSelected(Playlist::fromTracks(track->album()->tracks(), track));
    }
}

void ArtistAlbumWidget::clear()
{
    m_trackView->clear();
}
