#include "AlbumInfoView.h"

AlbumInfoView::AlbumInfoView(QWidget* parent) : QWidget(parent)
{
    m_album = NULL;

    m_cover = new QLabel();
    m_coverHeight = 175;
    m_coverWidth = 175;

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);

    setFixedSize(m_coverWidth, m_coverHeight + 40);
    setLayout(m_layout);
}

void AlbumInfoView::changeAlbum(Album* album)
{
    if(album)
    {
        if(m_album)
        {
            QObject::disconnect(m_album, SIGNAL(albumUpdated(Album*, quint8)), this, SLOT(onAlbumUpdated(Album*, quint8)));
        }

        if(!m_album || (m_album && m_album != album))
        {
            if(!album->cover())
            {
                m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(m_coverWidth,
                                                                                                       m_coverHeight,
                                                                                                       Qt::KeepAspectRatio,
                                                                                                       Qt::SmoothTransformation));
            }
            else
            {
                m_cover->setPixmap(QPixmap(album->cover().scaled(m_coverWidth,
                                                                 m_coverHeight,
                                                                 Qt::KeepAspectRatio,
                                                                 Qt::SmoothTransformation)));
            }
        }

        m_album = album;

        QObject::connect(m_album, SIGNAL(albumUpdated(Album*, quint8)), this, SLOT(onAlbumUpdated(Album*, quint8)));

        m_albumTitle->setText(m_album->title());
    }
}

void AlbumInfoView::onAlbumUpdated(Album* album, quint8 fields)
{
    if(album == m_album)
    {
        if(fields & Album::COVER)
        {
            if(!m_album->cover())
            {
                m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(m_coverWidth,
                                                                                                       m_coverHeight,
                                                                                                       Qt::KeepAspectRatio,
                                                                                                       Qt::SmoothTransformation));
            }
            else
            {
                m_cover->setPixmap(QPixmap(m_album->cover().scaled(m_coverWidth,
                                                                            m_coverHeight,
                                                                            Qt::KeepAspectRatio,
                                                                            Qt::SmoothTransformation)));
            }
        }
    }
}
