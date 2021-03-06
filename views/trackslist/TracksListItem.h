#ifndef TRACKSLISTITEM_H
#define TRACKSLISTITEM_H

#include <QObject>

#include "Track.h"
#include "Utils.h"

class TracksListItem : public QObject
{
        Q_OBJECT

    public:
        explicit TracksListItem(const QList<QVariant>& data, bool sort = true);
        explicit TracksListItem(Track* track, TracksListItem* parent);
        ~TracksListItem();

        QVariant data(int column) const;

        TracksListItem* parent() const;
        int row() const;

        TracksListItem* child(int row) const;
        int columnCount() const;
        int rowCount() const;

        int indexOf(Track* track);
        void prependChild(TracksListItem* item);
        void appendChild(TracksListItem* item);
        void insertChildAt(TracksListItem* item, int row);
        void removeFirstChild();
        void removeChild(TracksListItem* item);
        void removeChildAt(int row);
        void removeLastChild();
        void clear();

        Track* track() const;

    private slots:
        void onTrackRemoved(QObject* object);
        void onTrackUpdated(Track* track, quint8 fields);

    private:
        void sort();
        bool m_sort;

        Track* m_track;
        QList<QVariant> m_data;

        TracksListItem* m_parent;
        QList<TracksListItem*> m_childs;
};

#endif // TRACKSLISTITEM_H
