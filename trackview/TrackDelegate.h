#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QApplication>
#include <QPainter>
#include <QScrollBar>
#include <QStyledItemDelegate>

#include "TrackView.h"

class TrackView;

class TrackDelegate : public QStyledItemDelegate
{
    public:
        explicit TrackDelegate(const TrackView* TrackView, QObject* parent = 0);

        virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    private:
        const TrackView* c_trackView;
};

#endif // TRACKDELEGATE_H
