#include "ScrollableArea.h"

#include <QCommonStyle>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QScrollBar>

#include "GuiUtils.h"
#include "TrackLoader.h"
#include "Track.h"

ScrollableArea::ScrollableArea(QWidget* parent) : QScrollArea(parent)
{
    setAcceptDrops(true);
    setStyleSheet(GuiUtils::SCROLLABLE_AREA_STYLE);
    setWidgetResizable(true);

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    verticalScrollBar()->setStyle(new QCommonStyle);
    verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);
}

void ScrollableArea::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
}

void ScrollableArea::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QListIterator<QUrl> urlsIterator(urls);
    QVector<QFileInfo> filesInfo;

    while(urlsIterator.hasNext())
    {
        filesInfo.push_back(urlsIterator.next().toLocalFile());
    }

    emit filesDropped(filesInfo);
}

void ScrollableArea::resizeEvent(QResizeEvent* event)
{
    emit resized(event);
    QScrollArea::resizeEvent(event);
}
