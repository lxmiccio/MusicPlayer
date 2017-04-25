#include "TrackView.h"

#include "GuiUtils.h"

const quint8 TrackView::TRACK_INDEX;
const quint8 TrackView::TITLE_INDEX;
const quint8 TrackView::ALBUM_INDEX;
const quint8 TrackView::ARTIST_INDEX;
const quint8 TrackView::DURATION_INDEX;

TrackView::TrackView(quint8 mode, QWidget* parent) : QTableView(parent)
{
    m_mode = mode;

    m_trackModel = new TrackModel();

    m_filterProxy = new TrackFilterProxy();
    //m_filterProxy->setDynamicSortFilter(true);
    //m_filterProxy->setSourceModel(m_trackModel);
    //m_filterProxy->sort(0, Qt::AscendingOrder);
   //QObject::connect(m_trackModel, SIGNAL(rowsInserted(QModelIndex, int, int)), m_filterProxy, SLOT(invalidate()));
    setModel(m_trackModel);

    m_trackDelegate = new TrackDelegate(this);
    setItemDelegate(m_trackDelegate);

    horizontalHeader()->hide();
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setShowGrid(false);

    setStyleSheet(QString("QTableView {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"

                          "QTableView > QWidget > QWidget {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"));

    verticalScrollBar()->setStyle(new QCommonStyle());
    verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);

    QObject::connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onItemDoubleClicked(QModelIndex)));
}

TrackView::~TrackView()
{

}

QSize TrackView::fittingSize()
{
    return sizeHint();
}

quint8 TrackView::mode() const
{
    return m_mode;
}

TrackModel* TrackView::trackModel() const
{
    return m_trackModel;
}

int TrackView::rowCount() const
{
    return m_trackModel->rowCount();
}

int TrackView::columnCount() const
{
    return m_trackModel->columnCount();
}

void TrackView::propendItem(const Track* track)
{
    m_trackModel->propendItem(track);
}

void TrackView::appendItem(const Track* track)
{
    m_trackModel->appendItem(track);
}

void TrackView::removeItem(const Track* track)
{
    m_trackModel->removeItem(track);
}

void TrackView::insertItemAt(const Track* track, int row)
{
    m_trackModel->insertItemAt(track, row);
}

void TrackView::removeFirstItem()
{
    m_trackModel->removeFirstItem();
}

void TrackView::removeLastItem()
{
    m_trackModel->removeLastItem();
}

void TrackView::removeItemAt(int row)
{
    m_trackModel->removeItemAt(row);
}

void TrackView::clear()
{
    m_trackModel->clear();
}

void TrackView::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width() - TrackView::TRACK_WIDTH - TrackView::DURATION_WIDTH;

    if(m_mode == PlayingView::FULL)
    {
        setColumnWidth(TrackView::TRACK_INDEX, TrackView::TRACK_WIDTH);
        setColumnWidth(TrackView::TITLE_INDEX, width / 3);
        setColumnWidth(TrackView::ALBUM_INDEX, width / 3);
        setColumnWidth(TrackView::ARTIST_INDEX, width / 3);
        setColumnWidth(TrackView::DURATION_INDEX, TrackView::DURATION_WIDTH);
    }
    else
    {
        setColumnWidth(TrackView::TRACK_INDEX, TrackView::TRACK_WIDTH);
        setColumnWidth(TrackView::TITLE_INDEX, width);
        setColumnWidth(TrackView::DURATION_INDEX, TrackView::DURATION_WIDTH);

        setColumnHidden(TrackView::ALBUM_INDEX, true);
        setColumnHidden(TrackView::ARTIST_INDEX, true);
    }

    QTableView::resizeEvent(event);
}

QSize TrackView::sizeHint()
{
    QSize hint = QTableView::sizeHint();

    if(model())
    {
        quint16 width = verticalHeader()->width() + 4;
        for(quint8 i = 0; i < model()->columnCount(); ++i)
        {
            width += columnWidth(i);
        }

        quint16 height = horizontalHeader()->height() + 4;
        for(quint8 i = 0; i < model()->rowCount(); ++i)
        {
            height += rowHeight(i);
        }

        hint.setWidth(width);
        hint.setHeight(height);
    }

    return hint;
}

void TrackView::onItemDoubleClicked(const QModelIndex& index)
{
     emit trackDoubleClicked(m_trackModel->rootItem()->child(index.row())->track());
}
