#include "TrackList.h"

#include <QCommonStyle>
#include <QResizeEvent>
#include <QScrollBar>

TrackList::TrackList(quint8 mode, QWidget* parent) : QTableView(parent)
{
    m_mode = mode;

    TrackModel* trackModel = new TrackModel();
    setModel(trackModel);

    TrackDelegate* trackDelegate = new TrackDelegate(this);
    setItemDelegate(trackDelegate);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setShowGrid(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();

    setStyleSheet(QString("QTableView {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"

                          "QTableView > QWidget > QWidget {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"));

    verticalScrollBar()->setStyle(new QCommonStyle());
    verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical {"
                                               "background: transparent;"
                                               "border: 0px;"
                                               "margin: 0px 0px 0px 0px;"
                                               "width: 10px;"
                                               "}"

                                               "QScrollBar::handle:vertical {"
                                               "border-image: url(:/images/scroll-bar.jpg);"
                                               "border-radius: 2px;"
                                               "margin: 2px 0px 2px 4px;"
                                               "}"

                                               "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,"
                                               "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                                               "border: 0px;"
                                               "height: 0px;"
                                               "}"));
}

TrackList::~TrackList()
{

}

QSize TrackList::fittingSize()
{
    return sizeHint();
}

quint8 TrackList::mode() const
{
    return m_mode;
}

int TrackList::rowCount() const
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    return trackModel->rowCount();
}

int TrackList::columnCount() const
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    return trackModel->columnCount();
}

void TrackList::propendItem(const Track* track)
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    trackModel->propendItem(track);
}

void TrackList::appendItem(const Track* track)
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    trackModel->appendItem(track);
}

void TrackList::insertItemAt(const Track* track, int row)
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    trackModel->insertItemAt(track, row);
}

void TrackList::removeFirstItem()
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    trackModel->removeFirstItem();
}

void TrackList::removeLastItem()
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    trackModel->removeLastItem();
}

void TrackList::removeItemAt(int row)
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    trackModel->removeItemAt(row);
}

void TrackList::clear()
{
    TrackModel* trackModel = static_cast<TrackModel*>(model());
    trackModel->clear();
}

void TrackList::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width() - TrackList::TRACK_WIDTH - TrackList::DURATION_WIDTH;

    if(m_mode == TrackView::FULL)
    {
        setColumnWidth(0, TrackList::TRACK_WIDTH);
        setColumnWidth(1, width / 3);
        setColumnWidth(2, width / 3);
        setColumnWidth(3, width / 3);
        setColumnWidth(4, TrackList::DURATION_WIDTH);
    }
    else
    {
        this->setColumnWidth(0, TrackList::TRACK_WIDTH);
        this->setColumnWidth(1, width);
        this->setColumnWidth(4, TrackList::DURATION_WIDTH);

        this->setColumnHidden(2, true);
        this->setColumnHidden(3, true);
    }

    QTableView::resizeEvent(event);
}

QSize TrackList::sizeHint()
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
