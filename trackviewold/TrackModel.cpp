#include "TrackModel.h"

TrackModel::TrackModel(QObject* parent) : QAbstractItemModel(parent)
{
    m_rootItem = new TrackItem(QList<QVariant>() << "Track" << "Title" << "Album" << "Artist" << "Duration");
}

TrackModel::~TrackModel()
{
}

QVariant TrackModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return m_rootItem->data(column);
    }
    else
    {
        return QVariant();
    }
}

QVariant TrackModel::data(const QModelIndex& index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
    {
        return static_cast<TrackItem*>(index.internalPointer())->data(index.column());
    }
    else
    {
        return QVariant();
    }
}

QModelIndex TrackModel::parent(const QModelIndex& index) const
{
    TrackItem* parentItem = static_cast<TrackItem*>(index.internalPointer())->parent();

    if(index.isValid() && parentItem != m_rootItem)
    {
        return createIndex(parentItem->row(), 0, parentItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TrackModel::index(int row, int column, const QModelIndex& parent) const
{
    if(hasIndex(row, column, parent))
    {
        TrackItem* parentItem;

        if(parent.isValid())
        {
            parentItem = static_cast<TrackItem*>(parent.internalPointer());
        }
        else
        {
            parentItem = m_rootItem;
        }

        TrackItem* childItem = parentItem->child(row);

        if(childItem)
        {
            return createIndex(row, column, childItem);
        }
        else
        {
            return QModelIndex();
        }
    }
    else
    {
        return QModelIndex();
    }
}

int TrackModel::rowCount(const QModelIndex& parent) const
{
    TrackItem* parentItem;

    if(parent.isValid())
    {
        parentItem = static_cast<TrackItem*>(parent.internalPointer());
    }
    else
    {
        parentItem = m_rootItem;
    }

    return parentItem->rowCount();
}

int TrackModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return static_cast<TrackItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}

Qt::ItemFlags TrackModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
    {
        return QAbstractItemModel::flags(index);
    }
    else
    {
        return 0;
    }
}

void TrackModel::propendItem(Track* track)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_rootItem->prependChild(new TrackItem(track, m_rootItem));
    endInsertRows();
}

void TrackModel::appendItem(Track* track)
{
    beginInsertRows(QModelIndex(), m_rootItem->row(), m_rootItem->row());
    m_rootItem->appendChild(new TrackItem(track, m_rootItem));
    endInsertRows();
}

void TrackModel::insertItemAt(Track* track, int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginInsertRows(QModelIndex(), row, row);
        m_rootItem->insertChildAt(new TrackItem(track, m_rootItem), row);
        endInsertRows();
    }
}

void TrackModel::removeFirstItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, 0);
        m_rootItem->removeFirstChild();
        endRemoveRows();
    }
}

void TrackModel::removeLastItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
        m_rootItem->removeLastChild();
        endRemoveRows();
    }
}

void TrackModel::removeItem(Track* track)
{
    beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
    m_rootItem->removeChildAt(m_rootItem->indexOf(track));
    endRemoveRows();
}

void TrackModel::removeItemAt(int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginRemoveRows(QModelIndex(), row, row);
        m_rootItem->removeChildAt(row);
        endRemoveRows();
    }
}

void TrackModel::clear()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, m_rootItem->rowCount() - 1);
        m_rootItem->clear();
        endRemoveRows();
    }
}

TrackItem* TrackModel::rootItem()
{
    return m_rootItem;
}
