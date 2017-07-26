#include "TracksListModel.h"

TracksListModel::TracksListModel(QObject* parent) : QAbstractItemModel(parent)
{
    m_rootItem = new TracksListItem(QList<QVariant>() << "Track" << "Title" << "Album" << "Artist" << "Duration");
}

TracksListModel::~TracksListModel()
{
}

QVariant TracksListModel::headerData(int column, Qt::Orientation orientation, int role) const
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

QVariant TracksListModel::data(const QModelIndex& index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
    {
        return static_cast<TracksListItem*>(index.internalPointer())->data(index.column());
    }
    else
    {
        return QVariant();
    }
}

QModelIndex TracksListModel::parent(const QModelIndex& index) const
{
    TracksListItem* parentItem = static_cast<TracksListItem*>(index.internalPointer())->parent();

    if(index.isValid() && parentItem != m_rootItem)
    {
        return createIndex(parentItem->row(), 0, parentItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TracksListModel::index(int row, int column, const QModelIndex& parent) const
{
    if(hasIndex(row, column, parent))
    {
        TracksListItem* parentItem;

        if(parent.isValid())
        {
            parentItem = static_cast<TracksListItem*>(parent.internalPointer());
        }
        else
        {
            parentItem = m_rootItem;
        }

        TracksListItem* childItem = parentItem->child(row);

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

int TracksListModel::rowCount(const QModelIndex& parent) const
{
    TracksListItem* parentItem;

    if(parent.isValid())
    {
        parentItem = static_cast<TracksListItem*>(parent.internalPointer());
    }
    else
    {
        parentItem = m_rootItem;
    }

    return parentItem->rowCount();
}

int TracksListModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return static_cast<TracksListItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}

Qt::ItemFlags TracksListModel::flags(const QModelIndex &index) const
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

void TracksListModel::propendItem(Track* track)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_rootItem->prependChild(new TracksListItem(track, m_rootItem));
    endInsertRows();
}

void TracksListModel::appendItem(Track* track)
{
    beginInsertRows(QModelIndex(), m_rootItem->row(), m_rootItem->row());
    m_rootItem->appendChild(new TracksListItem(track, m_rootItem));
    endInsertRows();
}

void TracksListModel::insertItemAt(Track* track, int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginInsertRows(QModelIndex(), row, row);
        m_rootItem->insertChildAt(new TracksListItem(track, m_rootItem), row);
        endInsertRows();
    }
}

void TracksListModel::removeFirstItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, 0);
        m_rootItem->removeFirstChild();
        endRemoveRows();
    }
}

void TracksListModel::removeLastItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
        m_rootItem->removeLastChild();
        endRemoveRows();
    }
}

void TracksListModel::removeItem(Track* track)
{
    beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
    m_rootItem->removeChildAt(m_rootItem->indexOf(track));
    endRemoveRows();
}

void TracksListModel::removeItemAt(int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginRemoveRows(QModelIndex(), row, row);
        m_rootItem->removeChildAt(row);
        endRemoveRows();
    }
}

void TracksListModel::clear()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, m_rootItem->rowCount() - 1);
        m_rootItem->clear();
        endRemoveRows();
    }
}

TracksListItem* TracksListModel::rootItem()
{
    return m_rootItem;
}
