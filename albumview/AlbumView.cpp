#include "AlbumView.h"

#include <QApplication>
#include <QResizeEvent>

AlbumView::AlbumView(QWidget* parent) : QWidget(parent)
{
    m_upperSpacer = new QSpacerItem(0, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_leftSpacer = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_covers = QVector<Cover*>();
    m_layouts = QVector<QHBoxLayout*>();
    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->addItem(m_upperSpacer);
    m_layout->addItem(m_lowerSpacer);
    setLayout(m_layout);

    m_currentColumn = 0;
    m_currentRow = 0;
    m_albumsPerRow = albumsPerRow(rect().size().width());
}

AlbumView::~AlbumView()
{
#if 0
    qDeleteAll(m_covers);
    qDeleteAll(m_layouts);

    delete m_layout;
#endif
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
#endif

        delete i_item;
    }
}

void AlbumView::onScrollAreaResized(QResizeEvent* event)
{
    if(m_albumsPerRow != albumsPerRow(event->size().width()))
    {
        m_albumsPerRow = albumsPerRow(event->size().width());

        foreach(QHBoxLayout* i_layout, m_layouts)
        {
            clearLayout(i_layout);
        }
        m_layouts.clear();

        m_currentColumn = 0;
        m_currentRow = 0;

        foreach(Cover* i_cover, m_covers)
        {
            i_cover->hide();

            if(m_currentColumn == 0)
            {
                QHBoxLayout* layout = new QHBoxLayout();
                layout->addItem(m_leftSpacer);
                layout->addItem(m_rightSpacer);
                layout->insertWidget(m_currentColumn + 1, i_cover);
                m_layouts.push_back(layout);

                m_layout->insertLayout(m_currentRow + 1, layout);
            }
            else
            {
                m_layouts.at(m_currentRow)->insertWidget(m_currentColumn + 1, i_cover);
            }

            if(++m_currentColumn == m_albumsPerRow)
            {
                m_currentColumn = 0;
                m_currentRow++;
            }

            i_cover->show();
        }
    }
}

void AlbumView::onTrackAdded(const Track& track)
{
    const Album* album = track.album();

    if(m_albums.indexOf(album) == -1)
    {
        m_albums.push_back(album);

        Cover* cover = new Cover(album);
        m_covers.push_back(cover);

        QObject::connect(cover, SIGNAL(coverClicked(const Album&)), this, SLOT(onCoverClicked(const Album&)));

        if(m_currentColumn == 0)
        {
            QHBoxLayout* layout = new QHBoxLayout();
            layout->addItem(m_leftSpacer);
            layout->addItem(m_rightSpacer);
            m_layouts.push_back(layout);
            m_layout->insertLayout(m_currentRow + 1, layout);
        }

        m_layouts.at(m_currentRow)->insertWidget(m_currentColumn + 1, cover);

        if(++m_currentColumn == m_albumsPerRow)
        {
            m_currentColumn = 0;
            m_currentRow++;
        }
    }
}

void AlbumView::onCoverClicked(const Album& album)
{
    emit coverClicked(album);
}

quint8 AlbumView::albumsPerRow(quint16 width)
{
    return (width - 12) / (Cover::COVER_WIDTH + 6);
}
