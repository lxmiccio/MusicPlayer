#include "ScrollableWidget.h"

#include "GuiUtils.h"
#include "Track.h"

ScrollableWidget::ScrollableWidget(QWidget* parent) : QScrollArea(parent)
{
    setAcceptDrops(true);
    setStyleSheet(GuiUtils::SCROLLABLE_AREA_STYLE);
    setWidgetResizable(true);

    horizontalScrollBar()->hide();

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    verticalScrollBar()->setStyle(new QCommonStyle);
    verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);
}

void ScrollableWidget::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
}

void ScrollableWidget::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QListIterator<QUrl> urlsIterator(urls);
    QVector<QFileInfo> filesInfo;

    while(urlsIterator.hasNext())
    {
        QFileInfo fileInfo(urlsIterator.next().toLocalFile());

        if(fileInfo.isDir())
        {
            QDirIterator directoryIterator(fileInfo.absoluteFilePath(), QStringList() << "*.flac" << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
            while(directoryIterator.hasNext())
            {
                filesInfo.push_back(directoryIterator.next());
            }
        }
        else
        {
            filesInfo.push_back(fileInfo);
        }
    }

    emit filesDropped(filesInfo);
}

void ScrollableWidget::resizeEvent(QResizeEvent* event)
{
    emit resized(event);
    QScrollArea::resizeEvent(event);
}

void ScrollableWidget::clearLayout(QLayout* layout)
{
    QLayoutItem* i_item;

    while((i_item = layout->takeAt(0)) != NULL)
    {
        if(i_item->layout())
        {
            deleteLayout(i_item->layout());
            delete i_item->layout();
        }
    }
}

void ScrollableWidget::deleteLayout(QLayout* layout)
{
    if(layout && layout->count() > 0)
    {
        QLayoutItem* i_item;

        while((i_item = layout->takeAt(0)) != NULL)
        {
            if(i_item->layout())
            {
                deleteLayout(i_item->layout());
                delete i_item->layout();
            }

            if(i_item->widget())
            {
                delete i_item->widget();
            }

            delete i_item;
        }
    }
}
