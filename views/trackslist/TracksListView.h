#ifndef TRACKSLISTVIEW_H
#define TRACKSLISTVIEW_H

#include <QAction>
#include <QCommonStyle>
#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>
#include <QResizeEvent>
#include <QScrollBar>
#include <QTableView>

#include "HttpRequestWorker.h"
#include "TracksListDelegate.h"
#include "TracksListModel.h"

class TracksListDelegate;

class TracksListView : public QTableView
{
    Q_OBJECT

public:

    static const quint8 TRACK = 1;
    static const quint8 TITLE = 2;
    static const quint8 ALBUM = 4;
    static const quint8 ARTIST = 8;
    static const quint8 DURATION = 16;

    static const quint8 FULL = TRACK | TITLE | ALBUM | ARTIST | DURATION;
    static const quint8 REDUCED = TRACK | TITLE | DURATION;

    static const quint8 TRACK_INDEX = 0;
    static const quint8 TITLE_INDEX = 1;
    static const quint8 ALBUM_INDEX = 2;
    static const quint8 ARTIST_INDEX = 3;
    static const quint8 DURATION_INDEX = 4;

    static const quint8 TRACK_WIDTH = 100;
    static const quint8 DURATION_WIDTH = 100;

    static const quint8 LEFT_MARGIN = 38;
    static const quint8 MARGIN = 10;
    static const quint8 RIGHT_MARGIN = 38;

    explicit TracksListView(quint8 mode, QWidget* parent = 0);
    ~TracksListView();

    QSize fittingSize();
    quint8 mode() const;

    TracksListModel* tracksListModel() const;

    int rowCount() const;
    int columnCount() const;
    void propendItem(Track* track);
    void insertItemAt(Track* track, int row);
    void removeFirstItem();
    void removeLastItem();
    void removeItemAt(int row);
    void clear();

public slots:
    void appendItem(Track* track);
    void removeItem(Track* track);

signals:
    void trackClicked(Track* track);
    void trackDoubleClicked(Track* track);

protected:
    virtual void resizeEvent(QResizeEvent* event);
    virtual QSize sizeHint();

private slots:
    void onContextMenuRequested(QPoint position);
    void onItemClicked(const QModelIndex& index);
    void onItemDoubleClicked(const QModelIndex& index);

private:
    TracksListModel* m_tracksListModel;
    TracksListDelegate* m_tracksListDelegate;

    quint8 m_mode;
};

#endif // TRACKSLISTVIEW_H
