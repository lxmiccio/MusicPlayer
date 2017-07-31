#include "TrackInfoView.h"

TrackInfoView::TrackInfoView(QWidget* parent) : QWidget(parent)
{
    m_track = NULL;

    m_cover = new QLabel();
    m_coverHeight = 175;
    m_coverWidth = 175;

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignCenter);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_artistName = new ElidedLabel();
    m_artistName->setAlignment(Qt::AlignCenter);
    m_artistName->setStyleSheet(QString("color: white;"));

    m_lyrics = new QLabel();
    m_lyrics->setAlignment(Qt::AlignCenter);
    m_lyrics->setStyleSheet(QString("color: white;"));

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_albumTitle);
    m_layout->addWidget(m_artistName);
//    m_layout->addWidget(m_lyrics);

    setFixedSize(m_coverWidth, m_coverHeight + 40);
    setLayout(m_layout);
}

void TrackInfoView::changeTrack(Track* track)
{
    if(track)
    {
        if(m_track)
        {
            QObject::disconnect(m_track, SIGNAL(trackUpdated(Track*, quint8)), this, SLOT(onTrackUpdated(Track*, quint8)));
            QObject::disconnect(m_track->album(), SIGNAL(albumUpdated(Album*, quint8)), this, SLOT(onAlbumUpdated(Album*, quint8)));
            QObject::disconnect(m_track->album()->artist(), SIGNAL(artistUpdated(Artist*, quint8)), this, SLOT(onArtistUpdated(Artist*, quint8)));
        }

        if(!m_track || (m_track && m_track->album() != track->album()))
        {
            if(!track->album()->cover())
            {
                m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(m_coverWidth,
                                                                                                       m_coverHeight,
                                                                                                       Qt::KeepAspectRatio,
                                                                                                       Qt::SmoothTransformation));
            }
            else
            {
                m_cover->setPixmap(QPixmap(track->album()->cover().scaled(m_coverWidth,
                                                                            m_coverHeight,
                                                                            Qt::KeepAspectRatio,
                                                                            Qt::SmoothTransformation)));
            }
        }

        m_track = track;
        QObject::connect(m_track, SIGNAL(trackUpdated(Track*, quint8)), this, SLOT(onTrackUpdated(Track*, quint8)));
        QObject::connect(m_track->album(), SIGNAL(albumUpdated(Album*, quint8)), this, SLOT(onAlbumUpdated(Album*, quint8)));
        QObject::connect(m_track->album()->artist(), SIGNAL(artistUpdated(Artist*, quint8)), this, SLOT(onArtistUpdated(Artist*, quint8)));


        m_albumTitle->setText(m_track->album()->title());
        m_artistName->setText(m_track->album()->artist()->name());
        m_lyrics->setText(m_track->lyrics());
    }
}

void TrackInfoView::onTrackUpdated(Track* track, quint8 fields)
{
    if(track == m_track)
    {
        if(fields & Track::LYRICS)
        {
            m_lyrics->setText(m_track->lyrics());
        }
    }
}

void TrackInfoView::onAlbumUpdated(Album* album, quint8 fields)
{
    if(album == m_track->album())
    {
        if(fields & Album::COVER)
        {
            if(!m_track->album()->cover())
            {
                m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(m_coverWidth,
                                                                                                       m_coverHeight,
                                                                                                       Qt::KeepAspectRatio,
                                                                                                       Qt::SmoothTransformation));
            }
            else
            {
                m_cover->setPixmap(QPixmap(m_track->album()->cover().scaled(m_coverWidth,
                                                                            m_coverHeight,
                                                                            Qt::KeepAspectRatio,
                                                                            Qt::SmoothTransformation)));
            }
        }
    }
}

void TrackInfoView::onArtistUpdated(Artist* artist, quint8 fields)
{
    if(artist == m_track->album()->artist())
    {
        if(fields & Artist::NAME)
        {
            m_artistName->setText(m_track->album()->artist()->name());
        }
    }
}
