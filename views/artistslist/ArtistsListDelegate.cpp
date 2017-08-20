#include "ArtistsListDelegate.h"

ArtistsListDelegate::ArtistsListDelegate(ArtistsListView* artistsListView, QObject* parent) : QStyledItemDelegate(parent)
{
    m_artistsListView = artistsListView;
}

QWidget* ArtistsListDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    return NULL;
}

void ArtistsListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    ArtistsListItem* artistsListItem = static_cast<ArtistsListItem*>(index.data().value<void*>());

    if(option.state & QStyle::State_Selected)
    {
        QRect rect = option.rect;
        rect.setSize(artistsListItem->sizeHint());
        painter->fillRect(rect.adjusted(0, 3, 0, -3), QColor(0, 0, 0, 75));
    }

    artistsListItem->render(painter, option.rect.adjusted(30, 35, 30, 35).topLeft(), QRegion(), QWidget::DrawChildren);
}

QSize ArtistsListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    ArtistsListItem* artistsListItem = static_cast<ArtistsListItem*>(index.data().value<void*>());
    return artistsListItem->size();
}
