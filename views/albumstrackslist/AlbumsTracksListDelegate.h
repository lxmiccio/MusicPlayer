#ifndef ALBUMSTRACKSLISTDELEGATE_H
#define ALBUMSTRACKSLISTDELEGATE_H

#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>

#include "AlbumsTracksListView.h"

class AlbumsTracksListView;

class AlbumsTracksListDelegate : public QStyledItemDelegate
{
    public:
        AlbumsTracksListDelegate(AlbumsTracksListView* listView, QObject* parent = 0);

        bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

        virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

    private:
        AlbumsTracksListView* m_listView;
};

#endif // ALBUMSTRACKSLISTDELEGATE_H
