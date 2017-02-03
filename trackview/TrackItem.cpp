#include "TrackItem.h"

TrackItem::TrackItem(const QList<QVariant>& data, TrackItem* parent)
{
    c_track = NULL;
    m_parent = parent;
    m_data = data;
}

TrackItem::TrackItem(const Track* track, TrackItem* parent)
{
    c_track = track;
    m_parent = parent;
    m_data << QVariant(track->track()) << QVariant(track->title()) << QVariant(Utils::secondsToMinutes(track->duration()));
}

TrackItem::~TrackItem()
{
    qDeleteAll(m_childs);
}

QVariant TrackItem::data(int column) const
{
    return m_data.value(column);
}

TrackItem *TrackItem::parent() const
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

void TrackItem::prependChild(TrackItem* item)
{
    m_childs.prepend(item);
}

void TrackItem::appendChild(TrackItem* item)
{
    m_childs.append(item);
}

void TrackItem::insertChildAt(TrackItem* item, int row)
{
    m_childs.insert(row, item);
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
        delete m_childs.at(row);
        m_childs.removeAt(row);
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
