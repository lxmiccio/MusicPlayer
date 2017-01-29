#include "AlbumView.h"

#include <QResizeEvent>

#include "MusicLibrary.h"

AlbumView::AlbumView(QWidget* parent) : QWidget(parent)
{
    m_leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_upperSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_middleHorizontalSpacer = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_middleVerticalSpacer = new QSpacerItem(0, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_covers = QVector<Cover*>();
    m_layouts = QVector<QHBoxLayout*>();
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(40, 16, 40, 12);
    m_layout->addItem(m_upperSpacer);
    m_layout->addItem(m_lowerSpacer);
    setLayout(m_layout);

    m_albumCurrentColumn = 0;
    m_currentColumn = 0;
    m_currentRow = 1;
    m_albumsPerRow = albumsPerRow(rect().size().width());

    MusicLibrary* musicLibrary = MusicLibrary::instance();
    QObject::connect(musicLibrary, SIGNAL(albumAdded(const Album*)), this, SLOT(onAlbumAdded(const Album*)));
}

AlbumView::~AlbumView()
{
#if 0
    qDeleteAll(m_covers);
    qDeleteAll(m_layouts);

    delete m_layout;
#endif
}

void AlbumView::onScrollAreaResized(QResizeEvent* event)
{
    m_middleHorizontalSpacer->changeSize(horizontalSpacerWidth(event->size().width()), 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    if(m_albumsPerRow != albumsPerRow(event->size().width()))
    {
        m_albumsPerRow = albumsPerRow(event->size().width());
        repaintCovers();
    }

    m_layout->invalidate();
}

void AlbumView::repaintCovers()
{
    foreach(QHBoxLayout* i_layout, m_layouts)
    {
        clearLayout(i_layout);
    }
    m_layouts.clear();
    m_layout->removeItem(m_middleVerticalSpacer);

    m_currentColumn = 0;
    m_currentRow = 1;
    m_albumCurrentColumn = 0;

    foreach(Cover* i_cover, m_covers)
    {
        if(m_albumCurrentColumn == 0)
        {
            QHBoxLayout* layout = new QHBoxLayout();
            layout->addItem(m_leftSpacer);
            m_currentColumn++;

            if(m_currentRow == 1)
            {
                m_layout->insertLayout(m_currentRow, layout);
                m_currentRow++;
            }
            else
            {
                m_layout->insertItem(m_currentRow, m_middleVerticalSpacer);
                m_currentRow++;
                m_layout->insertLayout(m_currentRow, layout);
                m_currentRow++;
            }

            layout->addItem(m_rightSpacer);

            m_layouts.push_back(layout);
        }

        m_layouts.at(m_layouts.size() - 1)->insertWidget(m_currentColumn, i_cover);
        m_albumCurrentColumn++;
        m_currentColumn++;

        if(m_albumCurrentColumn == m_albumsPerRow)
        {
            m_albumCurrentColumn = 0;
            m_currentColumn = 0;
        }
        else
        {
            m_layouts.at(m_layouts.size() - 1)->insertItem(m_currentColumn, m_middleHorizontalSpacer);
            m_currentColumn++;
        }
    }
}

void AlbumView::onAlbumAdded(const Album* album)
{
    if(album)
    {
        QMutexLocker locker(&m_mutex);

        Cover* cover = new Cover(album);
        QObject::connect(cover, SIGNAL(coverClicked(const Album&)), this, SLOT(onCoverClicked(const Album&)));
        m_covers.push_back(cover);

        qSort(m_covers.begin(), m_covers.end(), [] (const Cover* cover1, const Cover* cover2) -> bool
        {
            if(cover1->album().artist()->name() != cover2->album().artist()->name())
            {
                return cover1->album().artist()->name() < cover2->album().artist()->name();
            }
            else
            {
                return cover1->album().title() < cover2->album().title();
            }
        });

        repaintCovers();
    }
}

void AlbumView::onCoverClicked(const Album& album)
{
    emit coverClicked(album);
}

void AlbumView::clearLayout(QLayout* layout)
{
    QLayoutItem* i_item;

    while((i_item = layout->takeAt(0)) != NULL)
    {
        if(i_item->layout())
        {
            clearLayout(i_item->layout());
            delete i_item->layout();
        }
#if 0
        if(i_item->widget())
        {
            delete i_item->widget();
        }

        delete i_item;
#endif
    }
}

quint8 AlbumView::albumsPerRow(quint16 width)
{
    return (width - 80) / (Cover::COVER_WIDTH + 32);
}

quint8 AlbumView::horizontalSpacerWidth(quint16 width)
{
    return (width - 80 - Cover::COVER_WIDTH * albumsPerRow(width)) / albumsPerRow(width);
}
