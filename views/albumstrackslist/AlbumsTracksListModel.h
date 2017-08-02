#ifndef ALBUMSTRACKSLISTMODEL_H
#define ALBUMSTRACKSLISTMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "AlbumsTracksListItem.h"

class AlbumsTracksListModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        explicit AlbumsTracksListModel(bool sort = true, QObject* parent = 0);
        ~AlbumsTracksListModel();

        QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        QVariant data(const QModelIndex& index, int role) const;
        QModelIndex parent(const QModelIndex& index) const;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        Qt::ItemFlags flags(const QModelIndex& index) const;

        void propendItem(Album* album);
        void appendItem(Album* album);
        void insertItemAt(Album* album, int row);
        void removeFirstItem();
        void removeLastItem();
        void removeItem(Album* album);
        void removeItemAt(int row);
        void clear();

        AlbumsTracksListItem* rootItem();

    private:
        AlbumsTracksListItem* m_rootItem;
};

#endif // ALBUMSTRACKSLISTMODEL_H
