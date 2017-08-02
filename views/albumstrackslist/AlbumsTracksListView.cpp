#include "AlbumsTracksListView.h"

#include <QCommonStyle>
#include <QScrollBar>

#include "GuiUtils.h"

AlbumsTracksListView::AlbumsTracksListView(bool sort, QWidget* parent) : QListView(parent)
{
    m_albumsTracksListModel = new AlbumsTracksListModel(sort);
    setModel(m_albumsTracksListModel);

    m_albumsTracksListDelegate = new AlbumsTracksListDelegate(this);
    setItemDelegate(m_albumsTracksListDelegate);

   // setSelectionBehavior(QAbstractItemView::SelectItems);
   // setSelectionMode(QAbstractItemView::NoSelection);
    setUniformItemSizes(true);

    setStyleSheet(QString("QListView {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"));

    verticalScrollBar()->setStyle(new QCommonStyle());
    verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);

    setGridSize(QSize(700, 700));
    setMovement(QListView::Static);
}

AlbumsTracksListView::~AlbumsTracksListView()
{

}

AlbumsTracksListModel* AlbumsTracksListView::albumsTracksListModel() const
{
    return m_albumsTracksListModel;
}

int AlbumsTracksListView::rowCount() const
{
    return m_albumsTracksListModel->rowCount();
}

int AlbumsTracksListView::columnCount() const
{
    return m_albumsTracksListModel->columnCount();
}

void AlbumsTracksListView::propendItem(Album* album)
{
    m_albumsTracksListModel->propendItem(album);
}

void AlbumsTracksListView::appendItem(Album* album)
{
    m_albumsTracksListModel->appendItem(album);
}

void AlbumsTracksListView::removeItem(Album* album)
{
    m_albumsTracksListModel->removeItem(album);
}

void AlbumsTracksListView::insertItemAt(Album* album, int row)
{
    m_albumsTracksListModel->insertItemAt(album, row);
}

void AlbumsTracksListView::removeFirstItem()
{
    m_albumsTracksListModel->removeFirstItem();
}

void AlbumsTracksListView::removeLastItem()
{
    m_albumsTracksListModel->removeLastItem();
}

void AlbumsTracksListView::removeItemAt(int row)
{
    m_albumsTracksListModel->removeItemAt(row);
}

void AlbumsTracksListView::clear()
{
    m_albumsTracksListModel->clear();
}

QSize AlbumsTracksListView::maxSize()
{
    QSize size;

    for(quint16 i = 0; i < m_albumsTracksListModel->rootItem()->rowCount(); ++i)
    {
        AlbumsTracksListItem* item = m_albumsTracksListModel->rootItem()->child(i);

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
