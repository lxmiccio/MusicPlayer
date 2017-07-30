#include "TracksListItem.h"

TracksListItem::TracksListItem(const QList<QVariant>& data, bool sort)
{
    m_track = NULL;

    m_data = data;
    m_sort = sort;
    m_parent = NULL;
}

TracksListItem::TracksListItem(Track* track, TracksListItem* parent)
{
    m_track = track;
    QObject::connect(m_track, SIGNAL(destroyed(QObject*)), parent, SLOT(onTrackRemoved(QObject*)));
    QObject::connect(m_track, SIGNAL(trackUpdated(Track*, quint8)), this, SLOT(onTrackUpdated(Track* ,quint8)));

    m_data << QVariant(track->track())
           << QVariant(track->title())
           << QVariant(track->album()->title())
           << QVariant(track->artist()->name())
           << QVariant(Utils::secondsToMinutes(track->duration()));

    m_sort = false;
    m_parent = parent;
}

TracksListItem::~TracksListItem()
{
    qDeleteAll(m_childs);
}

QVariant TracksListItem::data(int column) const
{
    return m_data.value(column);
}

TracksListItem* TracksListItem::parent() const
{
    return m_parent;
}

int TracksListItem::row() const
{
    if(m_parent)
    {
        return m_parent->m_childs.indexOf(const_cast<TracksListItem*>(this));
    }
    else
    {
        return 0;
    }
}

TracksListItem* TracksListItem::child(int row) const
{
    return m_childs.value(row);
}

int TracksListItem::columnCount() const
{
    return m_data.count();
}

int TracksListItem::rowCount() const
{
    return m_childs.count();
}

int TracksListItem::indexOf(Track* track)
{
    int index = -1;

    for(quint16 i = 0; i < m_childs.size(); ++i)
    {
        if(m_childs.at(i)->track() == track)
        {
            index = i;
            break;
        }
    }

    return index;
}

void TracksListItem::prependChild(TracksListItem* item)
{
    m_childs.prepend(item);
    sort();
}

void TracksListItem::appendChild(TracksListItem* item)
{
    m_childs.append(item);
    sort();
}

void TracksListItem::insertChildAt(TracksListItem* item, int row)
{
    m_childs.insert(row, item);
    sort();
}

void TracksListItem::removeFirstChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeFirst();
    }
}

void TracksListItem::removeLastChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeLast();
    }
}

void TracksListItem::removeChildAt(int row)
{
    if(row < m_childs.size())
    {
        delete m_childs.takeAt(row);
    }
}

void TracksListItem::clear()
{
    qDeleteAll(m_childs);
    m_childs.clear();
}

Track* TracksListItem::track() const
{
    return m_track;
}

void TracksListItem::onTrackRemoved(QObject* object)
{
    if(!m_childs.isEmpty())
    {
        Track* track = static_cast<Track*>(object);

        foreach(TracksListItem* i_child, m_childs)
        {
            if(i_child->track() == track)
            {
                m_childs.removeOne(i_child);
            }
        }
    }
}

void TracksListItem::onTrackUpdated(Track* track, quint8 fields)
{
    Q_UNUSED(fields);

    if(track == m_track)
    {
        m_data.clear();
        m_data << QVariant(track->track())
               << QVariant(track->title())
               << QVariant(track->album()->title())
               << QVariant(track->artist()->name())
               << QVariant(Utils::secondsToMinutes(track->duration()));
    }
}

void TracksListItem::sort()
{
    if(m_sort)
    {
        std::sort(m_childs.begin(), m_childs.end(), [] (const TracksListItem* tracksListItem1, const TracksListItem* tracksListItem2) -> bool
        {
            if(tracksListItem1->track()->artist()->name() != tracksListItem2->track()->artist()->name())
            {
                return tracksListItem1->track()->artist()->name() < tracksListItem2->track()->artist()->name();
            }
            else if(tracksListItem1->track()->album()->title() != tracksListItem2->track()->album()->title())
            {
                return tracksListItem1->track()->album()->title() < tracksListItem2->track()->album()->title();
            }
            else
            {
                return tracksListItem1->track()->track() < tracksListItem2->track()->track();
            }
        });
    }
}
