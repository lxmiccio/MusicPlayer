#include "ArtistsListView.h"

#include <QCommonStyle>
#include <QInputDialog>
#include <QMenu>
#include <QScrollBar>

#include "GuiUtils.h"
#include "MusicLibrary.h"

ArtistsListView::ArtistsListView(bool sort, QWidget* parent) : QListView(parent)
{
    m_artistsListModel = new ArtistsListModel(sort);
    setModel(m_artistsListModel);
    QObject::connect(m_artistsListModel, SIGNAL(itemUpdated()), SLOT(repaint()));

    m_artistsListDelegate = new ArtistsListDelegate(this);
    setItemDelegate(m_artistsListDelegate);

    setGridSize(QSize(250, 120));
    setMovement(QListView::Static);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setUniformItemSizes(true);

    setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onContextMenuRequested(QPoint)));

    setStyleSheet(QString("QListView {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"));

    verticalScrollBar()->setStyle(new QCommonStyle());
    verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);

    QObject::connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onItemClicked(QModelIndex)));
    QObject::connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
    QObject::connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onItemDoubleClicked(QModelIndex)));

    QObject::connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(onCurrentRowChanged(QModelIndex, QModelIndex)));
}

ArtistsListView::~ArtistsListView()
{

}

ArtistsListModel* ArtistsListView::artistsListModel() const
{
    return m_artistsListModel;
}

int ArtistsListView::rowCount() const
{
    return m_artistsListModel->rowCount();
}

int ArtistsListView::columnCount() const
{
    return m_artistsListModel->columnCount();
}

void ArtistsListView::propendItem(Artist* artist)
{
    m_artistsListModel->propendItem(artist);
}

void ArtistsListView::appendItem(Artist* artist)
{
    m_artistsListModel->appendItem(artist);
}

void ArtistsListView::removeItem(Artist* artist)
{
    m_artistsListModel->removeItem(artist);
}

void ArtistsListView::insertItemAt(Artist* artist, int row)
{
    m_artistsListModel->insertItemAt(artist, row);
}

void ArtistsListView::removeFirstItem()
{
    m_artistsListModel->removeFirstItem();
}

void ArtistsListView::removeLastItem()
{
    m_artistsListModel->removeLastItem();
}

void ArtistsListView::removeItemAt(int row)
{
    m_artistsListModel->removeItemAt(row);
}

void ArtistsListView::clear()
{
    m_artistsListModel->clear();
}

QSize ArtistsListView::maxSize()
{
    QSize size;

    for(quint16 i = 0; i < m_artistsListModel->rootItem()->rowCount(); ++i)
    {
        ArtistsListItem* item = m_artistsListModel->rootItem()->child(i);

        if(item->size().width() > size.width())
        {
            size.setWidth(item->size().width());
        }

        if(item->size().height() > size.height())
        {
            size.setHeight(item->size().height());
        }
    }

    return size;
}

void ArtistsListView::onContextMenuRequested(QPoint position)
{
}

void ArtistsListView::onItemClicked(const QModelIndex& index)
{
    emit artistClicked(m_artistsListModel->rootItem()->child(index.row())->artist());
}

void ArtistsListView::onItemEntered(const QModelIndex& index)
{
    emit artistEntered(m_artistsListModel->rootItem()->child(index.row())->artist());
}

void ArtistsListView::onItemPressed(const QModelIndex& index)
{
    emit artistPressed(m_artistsListModel->rootItem()->child(index.row())->artist());
}

void ArtistsListView::onItemDoubleClicked(const QModelIndex& index)
{
    emit artistDoubleClicked(m_artistsListModel->rootItem()->child(index.row())->artist());
}

void ArtistsListView::onCurrentRowChanged(QModelIndex current, QModelIndex previous)
{
    Q_UNUSED(previous);

    if(current.row() >= 0)
    {
        emit artistSelected(m_artistsListModel->rootItem()->child(current.row())->artist());
    }
}
