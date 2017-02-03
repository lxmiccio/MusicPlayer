#ifndef TRACKITEM_H
#define TRACKITEM_H

#include "Track.h"
#include "Utils.h"

class TrackItem
{
    public:
        explicit TrackItem(const QList<QVariant>& data, TrackItem* parent = 0);
        explicit TrackItem(const Track* track, TrackItem* parent = 0);
        ~TrackItem();

        QVariant data(int column) const;

        TrackItem* parent() const;
        int row() const;

        TrackItem* child(int row) const;
        int columnCount() const;
        int rowCount() const;

        void prependChild(TrackItem* item);
        void appendChild(TrackItem* item);
        void insertChildAt(TrackItem* item, int row);
        void removeFirstChild();
        void removeLastChild();
        void removeChildAt(int row);
        void clear();

        const Track* track() const;

    private:
        const Track* c_track;

        TrackItem* m_parent;
        QList<TrackItem*> m_childs;

        QList<QVariant> m_data;
};

#endif // TRACKITEM_H
