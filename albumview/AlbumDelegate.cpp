#include "AlbumDelegate.h"

AlbumDelegate::AlbumDelegate(AlbumGrid* albumGrid, QObject* parent) : QStyledItemDelegate(parent)
{
    m_albumGrid = albumGrid;
}

QWidget* AlbumDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    return NULL;
}

void AlbumDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(/*m_albumGrid->cellWidget(index.row(), index.column()) != m_albumGrid->m_spacerWidget && m_albumGrid->cellWidget(index.row(), index.column()) && */option.state & QStyle::State_Selected)
    {
        QRect rect;

        if(index.column() == 0)
        {
            rect = QRect(QPoint(option.rect.topLeft().x() + 10, option.rect.topLeft().y()), option.rect.bottomRight());
            painter->fillRect(rect, QColor(0, 0, 0, 10));
        }
        else if(index.column() == m_albumGrid->columnCount() - 1)
        {
            rect = QRect(option.rect.topLeft(), QPoint(option.rect.bottomRight().x() - 10, option.rect.bottomRight().y()));
            painter->fillRect(rect, QColor(0, 0, 0, 10));
        }
        else
        {
            rect = option.rect;
            painter->fillRect(rect, QColor(0, 0, 0, 10));
        }
    }
    else
    {
        painter->fillRect(option.rect, QColor(0, 0, 0, 0));
    }
}
