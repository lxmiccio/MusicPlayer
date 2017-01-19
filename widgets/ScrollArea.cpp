#include "ScrollArea.h"

#include <QCommonStyle>
#include <QDirIterator>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QScrollBar>

#include "Track.h"

ScrollArea::ScrollArea(QWidget* parent) : QScrollArea(parent)
{
    setAcceptDrops(true);
    setWidgetResizable(true);

    setStyleSheet(QString("QScrollArea {"
                              "background: transparent;"
                              "border: 0px;"
                          "}"
                          "QScrollArea > QWidget > QWidget {"
                            "background: transparent;"
                          "}"));

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    verticalScrollBar()->setStyle(new QCommonStyle);
    verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical {"
                                                   "background: transparent;"
                                                   "border: 0px;"
                                                   "margin: 0px 0px 10px 0px;"
                                                   "width: 10px;"
                                               "}"
                                               "QScrollBar::handle:vertical {"
                                                   "border-image: url(:/images/scroll-bar.jpg);"
                                                   "border-radius: 2px;"
                                                   "margin: 2px 4px 2px 0px;"
                                               "}"
                                               "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,"
                                               "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                                                   "border: 0px;"
                                                   "height: 0px;"
                                                   "width: 0px;"
                                               "}"));
}

void ScrollArea::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
}

void ScrollArea::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QListIterator<QUrl> urlIterator(urls);

    while(urlIterator.hasNext())
    {
        QFileInfo fileInfo(urlIterator.next().toLocalFile());
        if(fileInfo.isDir())
        {
            QDirIterator directoryIterator(fileInfo.absoluteFilePath(), QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
            while(directoryIterator.hasNext())
            {
                QFileInfo file(directoryIterator.next());
                if(Track::isSupportedSuffix(file.suffix()))
                {
                    emit fileDropped(file);
                }
            }
        }
        else
        {
            if(Track::isSupportedSuffix(fileInfo.suffix()))
            {
                emit fileDropped(fileInfo);
            }
        }
    }
}

void ScrollArea::resizeEvent(QResizeEvent* event)
{
    emit resized(event);

    QScrollArea::resizeEvent(event);
}
