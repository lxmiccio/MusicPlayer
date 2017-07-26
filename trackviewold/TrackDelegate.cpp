#include "TrackDelegate.h"

TrackDelegate::TrackDelegate(const TrackView* trackView, QObject* parent) : QStyledItemDelegate(parent)
{
    c_trackView = trackView;
}

QWidget* TrackDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    return NULL;
}

void TrackDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(option.state & QStyle::State_Selected)
    {
        QRect rect;

        if(index.column() == 0)
        {
            rect = QRect(QPoint(option.rect.topLeft().x() + 10, option.rect.topLeft().y()), option.rect.bottomRight());
            painter->fillRect(rect, QColor(0, 0, 0, 10));
        }
        else if(index.column() == c_trackView->columnCount())
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

    QFont font = QApplication::font();
    painter->setFont(font);

    QPen pen;
    pen.setColor(Qt::white);
    painter->setPen(pen);

    QString text = index.data().toString();

    if(index.column() == 0)
    {
        painter->drawText(option.rect.adjusted(TrackView::LEFT_MARGIN, 0, -TrackView::MARGIN, 0), Qt::AlignVCenter | Qt::AlignLeft, text);
    }
    else if(index.column() == c_trackView->columnCount())
    {
        painter->drawText(option.rect.adjusted(TrackView::MARGIN, 0, -TrackView::RIGHT_MARGIN, 0), Qt::AlignVCenter | Qt::AlignRight, text);
    }
    else
    {
        painter->drawText(option.rect.adjusted(TrackView::MARGIN, 0, -TrackView::MARGIN, 0), Qt::AlignVCenter | Qt::AlignLeft, text);
    }
}
