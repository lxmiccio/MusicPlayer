#include "AlbumsTracksListDelegate.h"

AlbumsTracksListDelegate::AlbumsTracksListDelegate(AlbumsTracksListView* listView, QObject* parent) : QStyledItemDelegate(parent)
{
    m_listView = listView;
}

bool AlbumsTracksListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    AlbumsTracksListModel* mod = (AlbumsTracksListModel*)model;
    AlbumsTracksListItem* item = mod->rootItem()->child(index.row());
    qDebug() << item;
    QApplication::sendEvent(item, event);
}

QWidget* AlbumsTracksListDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    return NULL;
}

void AlbumsTracksListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    AlbumsTracksListItem* item = static_cast<AlbumsTracksListItem*>(index.data().value<void*>());

    if(option.state & QStyle::State_Selected)
    {
        QRect rect = option.rect;
        rect.setSize(m_listView->maxSize());
        painter->fillRect(rect.adjusted(0, 3, 0, -3), QColor(0, 0, 0, 75));
    }

    item->render(painter, option.rect.adjusted(500, 35, 500, 35).topLeft(), QRegion(), QWidget::DrawChildren);
}

QSize AlbumsTracksListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    AlbumsTracksListItem* item = static_cast<AlbumsTracksListItem*>(index.data().value<void*>());
    return item->size();
}
