#ifndef TRACKMODEL_H
#define TRACKMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "TrackItem.h"

class TrackFilterProxy;
class TrackItem;

class TrackModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        explicit TrackModel(QObject* parent = 0);
        ~TrackModel();

        QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        QVariant data(const QModelIndex& index, int role) const;
        QModelIndex parent(const QModelIndex& index) const;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        Qt::ItemFlags flags(const QModelIndex& index) const;

        void propendItem(const Track* track);
        void appendItem(const Track* track);
        void insertItemAt(const Track* track, int row);
        void removeFirstItem();
        void removeLastItem();
        void removeItem(const Track* track);
        void removeItemAt(int row);
        void clear();

    public:
        TrackItem* m_rootItem;
};

#endif // TRACKMODEL_H
