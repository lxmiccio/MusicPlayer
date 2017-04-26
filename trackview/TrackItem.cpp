#include "TrackItem.h"

TrackItem::TrackItem(const QList<QVariant>& data, TrackItem* parent)
{
    c_track = NULL;

    m_data = data;
    m_parent = parent;
}

TrackItem::TrackItem(const Track* track, TrackItem* parent)
{
    c_track = track;
    QObject::connect(c_track, SIGNAL(destroyed(QObject*)), parent, SLOT(onTrackRemoved(QObject*)));
    QObject::connect(c_track, SIGNAL(trackUpdated(Track*, quint8)), this, SLOT(onTrackUpdated(Track* ,quint8)));

    m_data << QVariant(track->track())
           << QVariant(track->title())
           << QVariant(track->album()->title())
           << QVariant(track->artist()->name())
           << QVariant(Utils::secondsToMinutes(track->duration()));

    m_parent = parent;
}

TrackItem::~TrackItem()
{
    qDeleteAll(m_childs);
}

QVariant TrackItem::data(int column) const
{
    return m_data.value(column);
}

TrackItem* TrackItem::parent() const
{
    return m_parent;
}

int TrackItem::row() const
{
    if(m_parent)
    {
        return m_parent->m_childs.indexOf(const_cast<TrackItem*>(this));
    }
    else
    {
        return 0;
    }
}

TrackItem *TrackItem::child(int row) const
{
    return m_childs.value(row);
}

int TrackItem::columnCount() const
{
    return m_data.count();
}

int TrackItem::rowCount() const
{
    return m_childs.count();
}

int TrackItem::indexOf(Track* track)
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

void TrackItem::prependChild(TrackItem* item)
{
    m_childs.prepend(item);
    sort();
}

void TrackItem::appendChild(TrackItem* item)
{
    m_childs.append(item);
    sort();
}

void TrackItem::insertChildAt(TrackItem* item, int row)
{
    m_childs.insert(row, item);
    sort();
}

void TrackItem::removeFirstChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeFirst();
    }
}

void TrackItem::removeLastChild()
{
    if(!m_childs.isEmpty())
    {
        delete m_childs.takeLast();
    }
}

void TrackItem::removeChildAt(int row)
{
    if(row < m_childs.size())
    {
        delete m_childs.takeAt(row);
    }
}

void TrackItem::clear()
{
    qDeleteAll(m_childs);
    m_childs.clear();
}

const Track* TrackItem::track() const
{
    return c_track;
}

void TrackItem::onTrackRemoved(QObject* object)
{
    if(!m_childs.isEmpty())
    {
        Track* track = static_cast<Track*>(object);

        foreach(TrackItem* i_child, m_childs)
        {
            if(i_child->track() == track)
            {
                m_childs.removeOne(i_child);
            }
        }
    }
}

void TrackItem::onTrackUpdated(Track* track, quint8 fields)
{
    Q_UNUSED(fields);

    if(track == c_track)
    {
        m_data.clear();
        m_data << QVariant(track->track())
               << QVariant(track->title())
               << QVariant(track->album()->title())
               << QVariant(track->artist()->name())
               << QVariant(Utils::secondsToMinutes(track->duration()));
    }
}

void TrackItem::sort()
{
    std::sort(m_childs.begin(), m_childs.end(), [] (const TrackItem* trackItem1, const TrackItem* trackItem2) -> bool
    {
        if(trackItem1->track()->artist()->name() != trackItem2->track()->artist()->name())
        {
            return trackItem1->track()->artist()->name() < trackItem2->track()->artist()->name();
        }
        else if(trackItem1->track()->album()->title() != trackItem2->track()->album()->title())
        {
            return trackItem1->track()->album()->title() < trackItem2->track()->album()->title();
        }
        else
        {
            return trackItem1->track()->track() < trackItem2->track()->track();
        }
    });
}
