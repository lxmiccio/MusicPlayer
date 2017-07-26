#ifndef TRACKSLISTDELEGATE_H
#define TRACKSLISTDELEGATE_H

#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>

#include "TracksListView.h"

class TracksListView;

class TracksListDelegate : public QStyledItemDelegate
{
public:
    explicit TracksListDelegate(TracksListView* tracksListView, QObject* parent = 0);

    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    TracksListView* m_tracksListView;
};

#endif // TRACKSLISTDELEGATE_H
