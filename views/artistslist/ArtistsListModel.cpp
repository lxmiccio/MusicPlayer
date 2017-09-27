#include "ArtistsListModel.h"

ArtistsListModel::ArtistsListModel(bool sort, QObject* parent) : QAbstractItemModel(parent)
{
    m_rootItem = new ArtistsListItem(sort);
}

ArtistsListModel::~ArtistsListModel()
{
}

QVariant ArtistsListModel::headerData(int column, Qt::Orientation orientation, int role) const
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

QVariant ArtistsListModel::data(const QModelIndex& index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
    {
        return static_cast<ArtistsListItem*>(index.internalPointer())->data(index.column());
    }
    else
    {
        return QVariant();
    }
}

QModelIndex ArtistsListModel::parent(const QModelIndex& index) const
{
    ArtistsListItem* parentItem = static_cast<ArtistsListItem*>(index.internalPointer())->parent();

    if(index.isValid() && parentItem != m_rootItem)
    {
        return createIndex(parentItem->row(), 0, parentItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex ArtistsListModel::index(int row, int column, const QModelIndex& parent) const
{
    if(hasIndex(row, column, parent))
    {
        ArtistsListItem* parentItem;

        if(parent.isValid())
        {
            parentItem = static_cast<ArtistsListItem*>(parent.internalPointer());
        }
        else
        {
            parentItem = m_rootItem;
        }

        ArtistsListItem* childItem = parentItem->child(row);

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

int ArtistsListModel::rowCount(const QModelIndex& parent) const
{
    ArtistsListItem* parentItem;

    if(parent.isValid())
    {
        parentItem = static_cast<ArtistsListItem*>(parent.internalPointer());
    }
    else
    {
        parentItem = m_rootItem;
    }

    return parentItem->rowCount();
}

int ArtistsListModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return static_cast<ArtistsListItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}

Qt::ItemFlags ArtistsListModel::flags(const QModelIndex &index) const
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

void ArtistsListModel::propendItem(Artist* artist)
{
    beginInsertRows(QModelIndex(), 0, 0);
    ArtistsListItem* item = new ArtistsListItem(artist, m_rootItem);
    QObject::connect(item, SIGNAL(itemUpdated()), SIGNAL(itemUpdated()));
    m_rootItem->prependChild(item);
    endInsertRows();
}

void ArtistsListModel::appendItem(Artist* artist)
{
    beginInsertRows(QModelIndex(), m_rootItem->row(), m_rootItem->row());
    ArtistsListItem* item = new ArtistsListItem(artist, m_rootItem);
    QObject::connect(item, SIGNAL(itemUpdated()), SIGNAL(itemUpdated()));
    m_rootItem->appendChild(item);
    endInsertRows();

    QObject::connect(artist, SIGNAL(destroyed(QObject*)), SLOT(onArtistDestroyed(QObject*)));
}

void ArtistsListModel::insertItemAt(Artist* artist, int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginInsertRows(QModelIndex(), row, row);
        ArtistsListItem* item = new ArtistsListItem(artist, m_rootItem);
        QObject::connect(item, SIGNAL(itemUpdated()), SIGNAL(itemUpdated()));
        m_rootItem->insertChildAt(item, row);
        endInsertRows();
    }
}

void ArtistsListModel::removeFirstItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, 0);
        m_rootItem->removeFirstChild();
        endRemoveRows();
    }
}

void ArtistsListModel::removeLastItem()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
        m_rootItem->removeLastChild();
        endRemoveRows();
    }
}

void ArtistsListModel::removeItem(Artist* artist)
{
    beginRemoveRows(QModelIndex(), m_rootItem->rowCount() - 1, m_rootItem->rowCount() - 1);
    m_rootItem->removeChildAt(m_rootItem->indexOf(artist));
    endRemoveRows();
}

void ArtistsListModel::removeItemAt(int row)
{
    if(row < m_rootItem->rowCount())
    {
        beginRemoveRows(QModelIndex(), row, row);
        m_rootItem->removeChildAt(row);
        endRemoveRows();
    }
}

void ArtistsListModel::onArtistDestroyed(QObject* artist)
{
    removeItem(static_cast<Artist*>(artist));
}

void ArtistsListModel::clear()
{
    if(m_rootItem->rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, m_rootItem->rowCount() - 1);
        m_rootItem->clear();
        endRemoveRows();
    }
}

ArtistsListItem* ArtistsListModel::rootItem()
{
    return m_rootItem;
}

