#include "Cover.h"

Cover::Cover(const Album* album, QWidget* parent) : QWidget(parent)
{
    m_album = album;

    m_cover = new ClickableLabel();

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_artistName = new ElidedLabel();
    m_artistName->setAlignment(Qt::AlignCenter);
    m_artistName->setStyleSheet(QString("color: white;"));

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);
    m_layout->addWidget(m_artistName);

    setFixedSize(Cover::COVER_WIDTH, Cover::COVER_HEIGHT);
    setLayout(m_layout);

    QObject::connect(m_cover, SIGNAL(clicked()), this, SLOT(onCoverClicked()));
    QObject::connect(m_albumTitle, SIGNAL(leftButtonClicked()), this, SLOT(onCoverClicked()));
    QObject::connect(m_artistName, SIGNAL(leftButtonClicked()), this, SLOT(onCoverClicked()));

    setAlbum(m_album);
}

Cover::~Cover()
{
    delete m_layout;
}

const Album* Cover::album() const
{
    return m_album;
}

void Cover::setAlbum(const Album* album)
{
    if(album)
    {
        m_album = album;

        if(m_album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(Cover::COVER_WIDTH,
                                                                                                   Cover::COVER_HEIGHT,
                                                                                                   Qt::KeepAspectRatio,
                                                                                                   Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(m_album->cover().scaled(Cover::COVER_WIDTH,
                                                               Cover::COVER_HEIGHT,
                                                               Qt::KeepAspectRatio,
                                                               Qt::SmoothTransformation)));
        }

        m_albumTitle->setText(album->title());
        m_artistName->setText(album->artist()->name());
    }
}

void Cover::onAlbumChanged()
{
    Album* album = static_cast<Album*>(QObject::sender());

    if(album && album == m_album)
    {
        setAlbum(album);
    }
}

void Cover::onCoverClicked()
{
    emit coverClicked(m_album);
}
