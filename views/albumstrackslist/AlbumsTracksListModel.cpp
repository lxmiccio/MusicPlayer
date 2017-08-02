#include "AlbumsTracksListModel.h"

AlbumsTracksListModel::AlbumsTracksListModel(bool sort, QObject* parent) : QAbstractItemModel(parent)
{
    m_rootItem = new AlbumsTracksListItem(sort);
}

AlbumsTracksListModel::~AlbumsTracksListModel()
{
}

QVariant AlbumsTracksListModel::headerData(int column, Qt::Orientation orientation, int role) const
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

QVariant AlbumsTracksListModel::data(const QModelIndex& index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
    {
        return static_cast<AlbumsTracksListItem*>(index.internalPointer())->data(index.column());
    }
    else
    {
        return QVariant();
    }
}

QModelIndex AlbumsTracksListModel::parent(const QModelIndex& index) const
{
    AlbumsTracksListItem* parentItem = static_cast<AlbumsTracksListItem*>(index.internalPointer())->parent();

    if(index.isValid() && parentItem != m_rootItem)
    {
        return createIndex(parentItem->row(), 0, parentItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex AlbumsTracksListModel::index(int row, int column, const QModelIndex& parent) const
{
    if(hasIndex(row, column, parent))
    {
        AlbumsTracksListItem* parentItem;

        if(parent.isValid())
        {
            parentItem = static_cast<AlbumsTracksListItem*>(parent.internalPointer());
        }
        else
        {
            parentItem = m_rootItem;
        }

        AlbumsTracksListItem* childItem = parentItem->child(row);

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

int AlbumsTracksListModel::rowCount(const QModelIndex& parent) const
{
    AlbumsTracksListItem* parentItem;

    if(parent.isValid())
    {
        parentItem = static_cast<AlbumsTracksListItem*>(parent.internalPointer());
    }
    else
    {
        parentItem = m_rootItem;
    }

    return parentItem->rowCount();
}

int AlbumsTracksListModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return static_cast<AlbumsTracksListItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}

Qt::ItemFlags AlbumsTracksListModel::flags(const QModelIndex &index) const
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

void AlbumsTracksListModel::propendItem(Album* album)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_rootItem->prependChild(new AlbumsTracksListItem(album, m_rootItem));
    endInsertRows();
}

void AlbumsTracksListModel::appendItem(Album* album)
{
    beginInsertRows(QModelIndex(), m_rootItem->row(), m_rootItem->row());
    m_rootItem->appendChild(new AlbumsTracksListItem(album, m_rootItem));
    endInsertRows();
}

void AlbumsTracksListModel::insertItemAt(Album* album, int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginInsertRows(QModelIndex(), row, row);
        m_rootItem->insertChildAt(new AlbumsTracksListItem(album, m_rootItem), row);
        endInsertRows();
    }
}

void AlbumsTracksListModel::removeFirstItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, 0);
        m_rootItem->removeFirstChild();
        endRemoveRows();
    }
}

void AlbumsTracksListModel::removeLastItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
        m_rootItem->removeLastChild();
        endRemoveRows();
    }
}

void AlbumsTracksListModel::removeItem(Album* album)
{
    beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
    m_rootItem->removeChildAt(m_rootItem->indexOf(album));
    endRemoveRows();
}

void AlbumsTracksListModel::removeItemAt(int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginRemoveRows(QModelIndex(), row, row);
        m_rootItem->removeChildAt(row);
        endRemoveRows();
    }
}

void AlbumsTracksListModel::clear()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, m_rootItem->rowCount() - 1);
        m_rootItem->clear();
        endRemoveRows();
    }
}

AlbumsTracksListItem* AlbumsTracksListModel::rootItem()
{
    return m_rootItem;
}
