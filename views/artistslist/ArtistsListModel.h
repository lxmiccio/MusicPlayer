#ifndef ARTISTSLISTMODEL_H
#define ARTISTSLISTMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "ArtistsListItem.h"

class ArtistsListModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        ArtistsListModel(bool sort = true, QObject* parent = 0);
        ~ArtistsListModel();

        QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        QVariant data(const QModelIndex& index, int role) const;
        QModelIndex parent(const QModelIndex& index) const;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        Qt::ItemFlags flags(const QModelIndex& index) const;

        void propendItem(Artist* artist);
        void appendItem(Artist* artist);
        void insertItemAt(Artist* artist, int row);
        void removeFirstItem();
        void removeLastItem();
        void removeItem(Artist* artist);
        void removeItemAt(int row);
        void clear();

        ArtistsListItem* rootItem();

    signals:
        void itemUpdated();

    private:
        ArtistsListItem* m_rootItem;
};

#endif // ARTISTSLISTMODEL_H
