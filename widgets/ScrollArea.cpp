#include "ScrollArea.h"

#include <QCommonStyle>
#include <QDebug>
#include <QDirIterator>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QScrollBar>
#include <unistd.h>
#include "TrackLoader.h"
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

#if 0
    LoaderThread* loaderThread = new LoaderThread();
    QThread* thread = new QThread();

    QObject::connect(thread, SIGNAL(finished()), loaderThread, SLOT(deleteLater()));
    QObject::connect(this, SIGNAL(flacDropped(QFileInfo)), loaderThread, SLOT(loadFile(QFileInfo)));
    QObject::connect(loaderThread, SIGNAL(fileLoaded(Track)), this, SLOT(onTrackLoaded(Track)));

    loaderThread->moveToThread(thread);
    thread->start();

    emit this->flacDropped(urls.at(0).toLocalFile());
#endif

    QObject::connect(&l, SIGNAL(trackLoaded(Track*)), this, SLOT(onTrackLoaded(Track*)));
l.loadTracks(urls);
}

void ScrollArea::onTrackLoaded(Track* track)
{
    emit trackLoaded(track);
}

void ScrollArea::resizeEvent(QResizeEvent* event)
{
    emit resized(event);

    QScrollArea::resizeEvent(event);
}
