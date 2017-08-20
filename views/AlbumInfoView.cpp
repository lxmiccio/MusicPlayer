#include "AlbumInfoView.h"

AlbumInfoView::AlbumInfoView(QWidget* parent) : QWidget(parent)
{
    m_album = NULL;

    m_coverHeight = 175;
    m_coverWidth = 175;

    m_cover = new Label();
    m_cover->setAlignment(Qt::AlignBottom);
    m_cover->setFixedSize(m_coverWidth, m_coverHeight);
    m_cover->setRounded(true);
    QObject::connect(m_cover, SIGNAL(clicked()), SLOT(onCoverClicked()));

    m_spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    QFont font = QApplication::font();
    font.setBold(true);
    font.setPointSize(11);

    m_albumTitle = new ElidedLabel();
    m_albumTitle->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_albumTitle->setFont(font);
    m_albumTitle->setStyleSheet(QString("color: white;"));

    m_separator = new LineWidget(Qt::Horizontal);
    m_separator->setContentsMargins(0, 12, 0, 0);
    m_separator->setWidth(1);

    m_tracksListView = new TracksListView(TracksListView::REDUCED);

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->setMargin(0);
    m_leftLayout->setSpacing(0);
    m_leftLayout->addWidget(m_cover);
    m_leftLayout->addItem(m_spacer);

    m_rightLayout = new QVBoxLayout();
    m_rightLayout->setContentsMargins(36, 0, 0, 0);
    m_rightLayout->setSpacing(0);
    m_rightLayout->addWidget(m_albumTitle);
    m_rightLayout->addWidget(m_separator);
    m_rightLayout->addWidget(m_tracksListView);

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);
    m_layout->addLayout(m_leftLayout);
    m_layout->addLayout(m_rightLayout);

    setLayout(m_layout);
}

Album* AlbumInfoView::album()
{
    return m_album;
}

QSize AlbumInfoView::fittingSize()
{
    return QSize(m_coverWidth + m_tracksListView->sizeHint().width(), std::max(m_cover->sizeHint().height(), m_albumTitle->sizeHint().height() + 12 + m_separator->sizeHint().height() + m_tracksListView->sizeHint().height()));
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

        m_tracksListView->clear();
        foreach(Track* i_track, m_album->tracks())
        {
            m_tracksListView->appendItem(i_track);
        }
    }
}

void AlbumInfoView::onAlbumUpdated(Album* album, quint8 fields)
{
    if(album == m_album)
    {
        if(fields & Album::TITLE)
        {
            m_albumTitle->setText(m_album->title());
        }

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

void AlbumInfoView::onCoverClicked()
{
    emit coverClicked(m_album);
}
