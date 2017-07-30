#ifndef ARTISTSLISTDELEGATE_H
#define ARTISTSLISTDELEGATE_H

#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>

#include "ArtistsListView.h"

class ArtistsListView;

class ArtistsListDelegate : public QStyledItemDelegate
{
    public:
        ArtistsListDelegate(ArtistsListView* artistsListView, QObject* parent = 0);

        virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

    private:
        ArtistsListView* m_artistsListView;
};

#endif // ARTISTSLISTDELEGATE_
