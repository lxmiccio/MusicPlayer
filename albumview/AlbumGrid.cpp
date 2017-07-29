#include "AlbumGrid.h"

#include "GuiUtils.h"
#include "MusicLibrary.h"

AlbumGrid::AlbumGrid(QWidget* parent) : ScrollableWidget(parent)
{
    m_leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_upperSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_middleHorizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_middleVerticalSpacer = new QSpacerItem(0, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addItem(m_upperSpacer);
    m_layout->addItem(m_lowerSpacer);

    m_widget = new QWidget();
    m_widget->setLayout(m_layout);
    setWidget(m_widget);

    m_albumsCurrentColumn = 0;
    m_currentColumn = 0;
    m_currentRow = 1;
    m_albumsPerRow = albumsPerRow(rect().size().width());

    QObject::connect(this, SIGNAL(filesDropped(QVector<QFileInfo>)), MusicLibrary::instance(), SLOT(onTracksToLoad(QVector<QFileInfo>)));
    QObject::connect(MusicLibrary::instance(), SIGNAL(albumAdded(Album*)), this, SLOT(onAlbumAdded(Album*)));
}

AlbumGrid::~AlbumGrid()
{
    clearLayout(m_layout);
    delete m_layout;
    delete m_widget;
    //GuiUtils::deleteLayout(m_layout);
    //delete m_layout;
}

void AlbumGrid::resizeEvent(QResizeEvent* event)
{
    m_middleHorizontalSpacer->changeSize(horizontalSpacerWidth(event->size().width()), 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    if(m_albumsPerRow != albumsPerRow(event->size().width()))
    {
        m_albumsPerRow = albumsPerRow(event->size().width());
        repaintCovers();
    }

    m_layout->invalidate();
}

void AlbumGrid::repaintCovers()
{
    foreach(QHBoxLayout* i_layout, m_layouts)
    {
        clearLayout(i_layout);
        delete i_layout;
    }

    m_layouts.clear();
    m_layout->removeItem(m_middleVerticalSpacer);

    m_albumsCurrentColumn = 0;
    m_currentColumn = 0;
    m_currentRow = 1;

    foreach(AlbumCover* i_albumCover, m_albumCovers)
    {
        if(m_albumsCurrentColumn == 0)
        {
            QHBoxLayout* layout = new QHBoxLayout();
            m_layouts.push_back(layout);

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
        }

        m_layouts.at(m_layouts.size() - 1)->insertWidget(m_currentColumn, i_albumCover);
        m_albumsCurrentColumn++;
        m_currentColumn++;

        if(m_albumsCurrentColumn == m_albumsPerRow)
        {
            m_albumsCurrentColumn = 0;
            m_currentColumn = 0;
        }
        else
        {
            m_layouts.at(m_layouts.size() - 1)->insertItem(m_currentColumn, m_middleHorizontalSpacer);
            m_currentColumn++;
        }
    }
}

void AlbumGrid::onAlbumAdded(Album* album)
{
    if(album)
    {
        QMutexLocker locker(&m_mutex);

        AlbumCover* albumCover = new AlbumCover(album);
        QObject::connect(albumCover, SIGNAL(coverClicked(Album*)), this, SLOT(onCoverClicked(Album*)));
        m_albumCovers.push_back(albumCover);

        sort();
        repaintCovers();
    }
}

void AlbumGrid::onCoverClicked(Album* album)
{
    if(album)
    {
        emit coverClicked(album);
    }
}

void AlbumGrid::clearLayout(QLayout* layout)
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

void AlbumGrid::sort()
{
    qSort(m_albumCovers.begin(), m_albumCovers.end(), [] (const AlbumCover* albumCover1, const AlbumCover* albumCover2) -> bool
    {
        if(albumCover1->album()->artist()->name() != albumCover2->album()->artist()->name())
        {
            return albumCover1->album()->artist()->name() < albumCover2->album()->artist()->name();
        }
        else
        {
            return albumCover1->album()->title() < albumCover2->album()->title();
        }
    });
}

quint8 AlbumGrid::albumsPerRow(quint16 width)
{
    if(width)
    {
        return ((width) / (AlbumCover::COVER_WIDTH + 24));
    }
    else
    {
        return 1;
    }
}

quint8 AlbumGrid::horizontalSpacerWidth(quint16 width)
{
    if(albumsPerRow(width))
    {
        return ((width - (AlbumCover::COVER_WIDTH * albumsPerRow(width))) / albumsPerRow(width));
    }
    else
    {
        return 0;
    }
}
