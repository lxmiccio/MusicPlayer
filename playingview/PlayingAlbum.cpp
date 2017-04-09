#include "PlayingAlbum.h"

#include "Cover.h"

PlayingAlbum::PlayingAlbum(QWidget* parent) : QWidget(parent)
{
    m_cover = new ClickableLabel(this);
    m_cover->setFixedWidth(PlayingAlbum::IMAGE_WIDTH);
    m_cover->setFixedHeight(PlayingAlbum::IMAGE_HEIGHT);
    QObject::connect(m_cover, SIGNAL(clicked()), SIGNAL(coverClicked()));

    m_spacer1 = new QSpacerItem(0, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_artistName = new QLabel();
    m_artistName->setStyleSheet(QString("color: white;"));
    m_artistName->setWordWrap(true);

    m_spacer2 = new QSpacerItem(0, 4, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_albumTitle = new QLabel();
    m_albumTitle->setStyleSheet(QString("color: white;"));
    m_albumTitle->setWordWrap(true);

    m_spacer3 = new QSpacerItem(0, 48, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_cover);
    m_layout->addItem(m_spacer1);
    m_layout->addWidget(m_artistName);
    m_layout->addItem(m_spacer2);
    m_layout->addWidget(m_albumTitle);
    m_layout->addItem(m_spacer3);

    setFixedWidth(PlayingAlbum::WIDGET_WIDTH);
    setLayout(m_layout);
}

PlayingAlbum::~PlayingAlbum()
{
#if 0
    delete m_cover;
    delete m_spacer1;
    delete m_albumTitle;
    delete m_spacer2;
    delete m_artistName;
    delete m_spacer3;
    delete m_layout;
#endif
}

void PlayingAlbum::setAlbum(const Album* album)
{
    if(album)
    {
        c_album = album;

        if(c_album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(PlayingAlbum::IMAGE_WIDTH, PlayingAlbum::IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(c_album->cover().scaled(PlayingAlbum::IMAGE_WIDTH, PlayingAlbum::IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }

        m_albumTitle->setText(album->title());
        m_artistName->setText(album->artist()->name());
    }
}
