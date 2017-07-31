#include "AlbumCover.h"

AlbumCover::AlbumCover(Album* album, QWidget* parent) : ClickableWidget(parent)
{
    m_album = album;

    m_cover = new QLabel();

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_artistName = new ElidedLabel();
    m_artistName->setAlignment(Qt::AlignCenter);
    m_artistName->setStyleSheet(QString("color: white;"));

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);
    m_layout->addWidget(m_artistName);

    setFixedSize(AlbumCover::COVER_WIDTH, AlbumCover::COVER_HEIGHT);
    setLayout(m_layout);

    QObject::connect(this, SIGNAL(leftButtonClicked()), this, SLOT(onClicked()));

    setAlbum(m_album);
}

AlbumCover::AlbumCover(QWidget* parent) : ClickableWidget(parent)
{
    m_cover = new QLabel();

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_artistName = new ElidedLabel();
    m_artistName->setAlignment(Qt::AlignCenter);
    m_artistName->setStyleSheet(QString("color: white;"));

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);
    m_layout->addWidget(m_artistName);

    setFixedSize(AlbumCover::COVER_WIDTH, AlbumCover::COVER_HEIGHT);
    setLayout(m_layout);

    QObject::connect(this, SIGNAL(leftButtonClicked()), this, SLOT(onClicked()));
}

AlbumCover::~AlbumCover()
{
    delete m_layout;
}

const Album* AlbumCover::album() const
{
    return m_album;
}

void AlbumCover::setAlbum(Album* album)
{
    if(album)
    {
        m_album = album;

        if(m_album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(AlbumCover::COVER_WIDTH,
                                                                                                   AlbumCover::COVER_HEIGHT,
                                                                                                   Qt::KeepAspectRatio,
                                                                                                   Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(m_album->cover().scaled(AlbumCover::COVER_WIDTH,
                                                               AlbumCover::COVER_HEIGHT,
                                                               Qt::KeepAspectRatio,
                                                               Qt::SmoothTransformation)));
        }

        m_albumTitle->setText(album->title());
        m_artistName->setText(album->artist()->name());
    }
}

void AlbumCover::onAlbumChanged()
{
    Album* album = static_cast<Album*>(QObject::sender());

    if(album && album == m_album)
    {
        setAlbum(album);
    }
}

void AlbumCover::onClicked()
{
    emit coverClicked(m_album);
}
