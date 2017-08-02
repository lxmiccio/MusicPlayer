#include "AlbumsTracksListItem.h"

AlbumsTracksListItem::AlbumsTracksListItem(bool sort)
{
    m_sort = sort;
    m_parent = NULL;
}

AlbumsTracksListItem::AlbumsTracksListItem(Album* album, AlbumsTracksListItem* parent) : AlbumInfoView()
{
    m_album = album;
    QObject::connect(m_album, SIGNAL(albumUpdated(Album*, quint8)), SLOT(onAlbumUpdated(Album*, quint8)));


    AlbumInfoView::changeAlbum(m_album);

    setMinimumSize(700, 700);

    m_sort = false;
    m_parent = parent;
}

AlbumsTracksListItem::~AlbumsTracksListItem()
{
    qDeleteAll(m_childs);
}

QVariant AlbumsTracksListItem::data(int column) const
{
    Q_UNUSED(column)

    return QVariant::fromValue(static_cast<void*>(const_cast<AlbumsTracksListItem*>(this)));
}

AlbumsTracksListItem* AlbumsTracksListItem::parent() const
{
    return m_parent;
}

int AlbumsTracksListItem::row() const
{
    if(m_parent)
    {
        return m_parent->m_childs.indexOf(const_cast<AlbumsTracksListItem*>(this));
    }
    else
    {
        return 0;
    }
}

AlbumsTracksListItem* AlbumsTracksListItem::child(int row) const
{
    return m_childs.value(row);
}

int AlbumsTracksListItem::columnCount() const
{
    return 1;
}

int AlbumsTracksListItem::rowCount() const
{
    return m_childs.count();
}

int AlbumsTracksListItem::indexOf(Album* album)
{
    int index = -1;

    for(quint16 i = 0; i < m_childs.size(); ++i)
    {
        if(m_childs.at(i)->album() == album)
        {
            index = i;
            break;
        }
    }

    return index;
}

void AlbumsTracksListItem::prependChild(AlbumsTracksListItem* item)
{
    m_childs.prepend(item);
    sort();
}

void AlbumsTracksListItem::appendChild(AlbumsTracksListItem* item)
{
    m_childs.append(item);
    sort();
}

void AlbumsTracksListItem::insertChildAt(AlbumsTracksListItem* item, int row)
{
    m_childs.insert(row, item);
    sort();
}

void AlbumsTracksListItem::removeFirstChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeFirst();
    }
}

void AlbumsTracksListItem::removeLastChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeLast();
    }
}

void AlbumsTracksListItem::removeChildAt(int row)
{
    if(row < m_childs.size())
    {
        delete m_childs.takeAt(row);
    }
}

void AlbumsTracksListItem::clear()
{
    qDeleteAll(m_childs);
    m_childs.clear();
}

Album* AlbumsTracksListItem::album() const
{
    return m_album;
}

void AlbumsTracksListItem::sort()
{
    if(m_sort)
    {
        std::sort(m_childs.begin(), m_childs.end(), [] (const AlbumsTracksListItem* albumsTracksListItem1, const AlbumsTracksListItem* albumsTracksListItem2) -> bool
        {
            return albumsTracksListItem1->album()->title() < albumsTracksListItem2->album()->title();
        });
    }
}
