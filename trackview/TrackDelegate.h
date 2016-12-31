#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QStyledItemDelegate>

#include "TrackList.h"

class TrackDelegate : public QStyledItemDelegate
{
    public:
        explicit TrackDelegate(const TrackList* trackList, QObject* parent = 0);

        virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    private:
        const TrackList* c_trackList;
};

#endif // TRACKDELEGATE_H
