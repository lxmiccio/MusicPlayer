#include "TrackList.h"

#include <QCommonStyle>
#include <QResizeEvent>
#include <QScrollBar>
#include <QDebug>

TrackList::TrackList(QWidget* parent) : QTableView(parent)
{
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

void TrackList::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width() - TrackList::TRACK_WIDTH - TrackList::DURATION_WIDTH;

    this->setColumnWidth(TrackList::TRACK, TrackList::TRACK_WIDTH);
    this->setColumnWidth(TrackList::TITLE, width);
    this->setColumnWidth(TrackList::DURATION, TrackList::DURATION_WIDTH);

    QTableView::resizeEvent(event);
}
