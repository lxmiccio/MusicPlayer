#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QAction>
#include <QCommonStyle>
#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>
#include <QResizeEvent>
#include <QScrollBar>
#include <QTableView>

#include "TrackDelegate.h"
#include "TrackFilterProxy.h"
#include "TrackModel.h"
#include "PlayingView.h"
#include "SoundTouchManager.h"

class TrackDelegate;
class TrackFilterProxy;

class TrackView : public QTableView
{
        Q_OBJECT

    public:
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

        explicit TrackView(quint8 mode, QWidget* parent = 0);
        ~TrackView();

        QSize fittingSize();
        quint8 mode() const;

        TrackModel* trackModel() const;

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
        void trackDoubleClicked(Track* track);

    protected:
        virtual void resizeEvent(QResizeEvent* event);
        virtual QSize sizeHint();

    private slots:
        void onContextMenuRequested(QPoint position);
        void onItemDoubleClicked(const QModelIndex& index);

    private:
        TrackModel* m_trackModel;
        TrackFilterProxy* m_filterProxy;
        TrackDelegate* m_trackDelegate;

        SoundTouchManager* m_soundTouch;

        quint8 m_mode;
};

#endif // TRACKVIEW_H
