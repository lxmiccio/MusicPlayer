#include "AlbumCoverWidget.h"

AlbumCoverWidget::AlbumCoverWidget(Album* album, QWidget* parent) : ClickableWidget(parent)
{
    m_album = album;

    m_cover = new QLabel();

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet("color: white;");

    m_artistName = new ElidedLabel();
    m_artistName->setAlignment(Qt::AlignCenter);
    m_artistName->setStyleSheet("color: white;");

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);
    m_layout->addWidget(m_artistName);

    setFixedSize(AlbumCoverWidget::COVER_WIDTH, AlbumCoverWidget::COVER_HEIGHT);
    setLayout(m_layout);

    QObject::connect(this, SIGNAL(leftButtonClicked()), this, SLOT(onClicked()));

    setAlbum(m_album);
}

AlbumCoverWidget::AlbumCoverWidget(QWidget* parent) : ClickableWidget(parent)
{
    m_cover = new QLabel();

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet("color: white;");

    m_artistName = new ElidedLabel();
    m_artistName->setAlignment(Qt::AlignCenter);
    m_artistName->setStyleSheet("color: white;");

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);
    m_layout->addWidget(m_artistName);

    setFixedSize(AlbumCoverWidget::COVER_WIDTH, AlbumCoverWidget::COVER_HEIGHT);
    setLayout(m_layout);

    QObject::connect(this, SIGNAL(leftButtonClicked()), this, SLOT(onClicked()));
}

AlbumCoverWidget::~AlbumCoverWidget()
{
    deleteLayout(m_layout);
}

Album* AlbumCoverWidget::album() const
{
    return m_album;
}

void AlbumCoverWidget::setAlbum(Album* album)
{
    if(album)
    {
        m_album = album;
        QObject::connect(m_album, SIGNAL(albumUpdated(Album*, quint8)), this, SLOT(onAlbumChanged(Album*, quint8)));

        if(m_album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(AlbumCoverWidget::COVER_WIDTH,
                                                                                                   AlbumCoverWidget::COVER_HEIGHT,
                                                                                                   Qt::KeepAspectRatio,
                                                                                                   Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(m_album->cover().scaled(AlbumCoverWidget::COVER_WIDTH,
                                                               AlbumCoverWidget::COVER_HEIGHT,
                                                               Qt::KeepAspectRatio,
                                                               Qt::SmoothTransformation)));
        }

        m_albumTitle->setText(album->title());
        m_artistName->setText(album->artist() ? album->artist()->name() : "Unknown");
    }
}

void AlbumCoverWidget::onAlbumChanged(Album* album, quint8 fields)
{
    if(album && album == m_album)
    {
        if(fields & Album::TITLE)
        {
            m_albumTitle->setText(album->title());
        }
        else if(fields & Album::COVER)
        {
            m_cover->setPixmap(QPixmap(m_album->cover().scaled(AlbumCoverWidget::COVER_WIDTH,
                                                               AlbumCoverWidget::COVER_HEIGHT,
                                                               Qt::KeepAspectRatio,
                                                               Qt::SmoothTransformation)));
        }
        else if(fields & Album::ARTIST && album->artist())
        {
            m_artistName->setText(album->artist()->name());
        }
    }
}

void AlbumCoverWidget::onClicked()
{
    emit coverClicked(m_album);
}

