#ifndef TRACKITEM_H
#define TRACKITEM_H

#include <QObject>

#include "Track.h"
#include "TrackModel.h"
#include "Utils.h"

class TrackItem : public QObject
{
        Q_OBJECT

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

        int indexOf(Track* track);
        void prependChild(TrackItem* item);
        void appendChild(TrackItem* item);
        void insertChildAt(TrackItem* item, int row);
        void removeFirstChild();
        void removeChild(TrackItem* item);
        void removeChildAt(int row);
        void removeLastChild();
        void clear();

        const Track* track() const;

    private slots:
        void onTrackRemoved(QObject* object);
        void onTrackUpdated(Track* track, quint8 fields);

    private:
        void sort();

        const Track* c_track;
        QList<QVariant> m_data;

        TrackItem* m_parent;
        QList<TrackItem*> m_childs;
};

#endif // TRACKITEM_H
