#include "TrackAlbum.h"

#include <QApplication>
#include <QFont>

#include "Cover.h"

TrackAlbum::TrackAlbum(QWidget* parent) : QWidget(parent)
{
    QFont font = QApplication::font();
    font.setPointSize(13);

    m_cover = new ClickableLabel();
    m_cover->setAlignment(Qt::AlignCenter);
    QObject::connect(m_cover, SIGNAL(clicked()), this, SLOT(onCoverClicked()));

    m_spacer1 = new QSpacerItem(0, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_albumTitle = new QLabel();
    m_albumTitle->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    m_albumTitle->setFont(font);
    m_albumTitle->setWordWrap(true);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_spacer2 = new QSpacerItem(0, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_artistName = new QLabel();
    m_artistName->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    m_artistName->setFont(font);
    m_artistName->setWordWrap(true);
    m_artistName->setStyleSheet(QString("color: white;"));

    m_spacer3 = new QSpacerItem(0, 48, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_cover);
    m_layout->addItem(m_spacer1);
    m_layout->addWidget(m_albumTitle);
    m_layout->addItem(m_spacer2);
    m_layout->addWidget(m_artistName);
    m_layout->addItem(m_spacer3);

    setFixedWidth(TrackAlbum::WIDGET_WIDTH);
    setLayout(m_layout);
}

TrackAlbum::~TrackAlbum()
{
    delete m_cover;
    delete m_spacer1;
    delete m_albumTitle;
    delete m_spacer2;
    delete m_artistName;
    delete m_spacer3;
    delete m_layout;
}

void TrackAlbum::setAlbum(const Album* album)
{
    if(album)
    {
        c_album = album;

        if(c_album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(TrackAlbum::IMAGE_WIDTH, TrackAlbum::IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(c_album->cover().scaled(TrackAlbum::IMAGE_WIDTH, TrackAlbum::IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }

        m_albumTitle->setText(album->title());
        m_artistName->setText(album->artist()->name());
    }
}

void TrackAlbum::onCoverClicked()
{
    emit coverClicked();
}
