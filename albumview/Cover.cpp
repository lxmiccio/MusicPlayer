#include "Cover.h"

Cover::Cover(const Album* album, QWidget* parent) : QWidget(parent)
{
    c_album = album;

    m_cover = new ClickableLabel();

    if(!c_album->cover().isNull())
    {
        m_cover->setPixmap(QPixmap(c_album->cover().scaled(Cover::COVER_WIDTH, Cover::COVER_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    else
    {
        m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(Cover::COVER_WIDTH, Cover::COVER_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    m_albumTitle = new ElidedLabel(album->title());
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_artistName = new ElidedLabel(album->artist()->name());
    m_artistName->setAlignment(Qt::AlignCenter);
    m_artistName->setStyleSheet(QString("color: white;"));

    QObject::connect(m_cover, SIGNAL(clicked()), this, SLOT(onCoverClicked()));
    QObject::connect(m_albumTitle, SIGNAL(clicked()), this, SLOT(onCoverClicked()));
    QObject::connect(m_artistName, SIGNAL(clicked()), this, SLOT(onCoverClicked()));

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);
    m_layout->addWidget(m_artistName);

    setLayout(m_layout);

    setFixedSize(Cover::COVER_WIDTH, Cover::COVER_HEIGHT);
}

Cover::~Cover()
{
#if 0
    delete m_cover;
    delete m_albumTitle;
    delete m_artistName;
    delete m_layout;
#endif
}

const Album& Cover::album() const
{
    return *c_album;
}

void Cover::onCoverClicked()
{
    emit coverClicked(*c_album);
}
