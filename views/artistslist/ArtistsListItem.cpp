#include "ArtistsListItem.h"

ArtistsListItem::ArtistsListItem(bool sort)
{
    m_artist = NULL;
    m_artistName = NULL;
    m_cover = NULL;
    m_layout = NULL;

    m_sort = sort;
    m_parent = NULL;
}

ArtistsListItem::ArtistsListItem(Artist* artist, ArtistsListItem* parent)
{
    m_artist = artist;
    QObject::connect(m_artist, SIGNAL(albumAdded(Album*)), SLOT(onAlbumAdded(Album*)));
    QObject::connect(m_artist, SIGNAL(albumUpdated(Album*, quint8)), SLOT(onAlbumAdded(Album*)));
    QObject::connect(m_artist, SIGNAL(artistUpdated(Artist*, quint8)), SLOT(onArtistUpdated(Artist*, quint8)));
    m_artist->downloadImage();

    m_cover = new Label();
    m_cover->setAlignment(Qt::AlignCenter);
    m_cover->setContentsMargins(10, 10, 10, 10);
    m_cover->setRounded(true);

    if(m_artist && !m_artist->albums().isEmpty())
    {
        m_hasCover = true;
        m_cover->setPixmap(QPixmap(m_artist->albums().first()->cover().scaled(100,
                                                                              100,
                                                                              Qt::KeepAspectRatio,
                                                                              Qt::SmoothTransformation)));
    }
    else
    {
        m_hasCover = false;
        m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(100,
                                                                                               100,
                                                                                               Qt::KeepAspectRatio,
                                                                                               Qt::SmoothTransformation));
    }

    m_artistName = new QLabel(m_artist->name());
    m_artistName->setAlignment(Qt::AlignVCenter);
    m_artistName->setStyleSheet(QString("color: white;"));

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_artistName);

    setMinimumSize(300, 120);
    setLayout(m_layout);

    m_sort = false;
    m_parent = parent;
}

ArtistsListItem::~ArtistsListItem()
{
    qDeleteAll(m_childs);
}

QVariant ArtistsListItem::data(int column) const
{
    Q_UNUSED(column)

    return QVariant::fromValue(static_cast<void*>(const_cast<ArtistsListItem*>(this)));
}

ArtistsListItem* ArtistsListItem::parent() const
{
    return m_parent;
}

int ArtistsListItem::row() const
{
    if(m_parent)
    {
        return m_parent->m_childs.indexOf(const_cast<ArtistsListItem*>(this));
    }
    else
    {
        return 0;
    }
}

ArtistsListItem* ArtistsListItem::child(int row) const
{
    return m_childs.value(row);
}

int ArtistsListItem::columnCount() const
{
    return 1;
}

int ArtistsListItem::rowCount() const
{
    return m_childs.count();
}

int ArtistsListItem::indexOf(Artist* artist)
{
    int index = -1;

    for(quint16 i = 0; i < m_childs.size(); ++i)
    {
        if(m_childs.at(i)->artist() == artist)
        {
            index = i;
            break;
        }
    }

    return index;
}

void ArtistsListItem::prependChild(ArtistsListItem* item)
{
    m_childs.prepend(item);
    sort();
}

void ArtistsListItem::appendChild(ArtistsListItem* item)
{
    m_childs.append(item);
    sort();
}

void ArtistsListItem::insertChildAt(ArtistsListItem* item, int row)
{
    m_childs.insert(row, item);
    sort();
}

void ArtistsListItem::removeFirstChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeFirst();
    }
}

void ArtistsListItem::removeLastChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeLast();
    }
}

void ArtistsListItem::removeChildAt(int row)
{
    if(row < m_childs.size())
    {
        delete m_childs.takeAt(row);
    }
}

void ArtistsListItem::clear()
{
    qDeleteAll(m_childs);
    m_childs.clear();
}

Artist* ArtistsListItem::artist() const
{
    return m_artist;
}

void ArtistsListItem::onAlbumAdded(Album* album)
{
    if(!m_hasCover && album && !album->cover().isNull())
    {
        m_hasCover = true;
        m_cover->setPixmap(QPixmap(m_artist->albums().first()->cover().scaled(100,
                                                                              100,
                                                                              Qt::KeepAspectRatio,
                                                                              Qt::SmoothTransformation)));
    }
}

void ArtistsListItem::onArtistUpdated(Artist* artist, quint8 fields)
{
    if(artist == m_artist)
    {
        if(fields & Artist::NAME)
        {
            m_artistName->setText(m_artist->name());
        }

        if(fields & Artist::IMAGE)
        {
            if(!m_artist->image())
            {
                m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(100,
                                                                                                       100,
                                                                                                       Qt::KeepAspectRatio,
                                                                                                       Qt::SmoothTransformation));
            }
            else
            {
                m_hasCover = true;
                m_cover->setPixmap(QPixmap(m_artist->image().scaled(100,
                                                                    100,
                                                                    Qt::KeepAspectRatio,
                                                                    Qt::SmoothTransformation)));
            }
        }

        emit itemUpdated();
    }
}

void ArtistsListItem::sort()
{
    if(m_sort)
    {
        std::sort(m_childs.begin(), m_childs.end(), [] (const ArtistsListItem* artistsListItem1, const ArtistsListItem* artistsListItem2) -> bool
        {
            return artistsListItem1->artist()->name() < artistsListItem2->artist()->name();
        });
    }
}
