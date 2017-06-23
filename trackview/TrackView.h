#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QAction>
#include <QCommonStyle>
#include <QDebug>
#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>
#include <QResizeEvent>
#include <QScrollBar>
#include <QTableView>

#include <QRegExp>

#include "HttpRequestWorker.h"
#include "PlayingView.h"
#include "SoundTouchManager.h"
#include "TrackDelegate.h"
#include "TrackFilterProxy.h"
#include "TrackModel.h"

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

        void handle_result(HttpRequestWorker* wrk)
        {
            QString url_str = wrk->m_lyricsUrl;

            HttpRequestInput input(url_str, "GET");

            HttpRequestWorker* worker = new HttpRequestWorker(this);
            QObject::connect(worker, SIGNAL(on_execution_finished(HttpRequestWorker*)), this, SLOT(handle_result_1(HttpRequestWorker*)));
            worker->execute(&input);
        }

        void handle_result_1(HttpRequestWorker* wrk)
        {

            QRegExp rx("<p([^>]*)content([^>]*)>(.*)</p>");
            rx.setMinimal(true);
           // QRegExp rx("<p([^>]*)content([^>]*)>.*?<?p>");

            QStringList list;
            int pos = 0;

            while ((pos = rx.indexIn(wrk->m_response, pos)) != -1) {
                list << rx.cap(3);
                pos += rx.matchedLength();
            }

            qDebug() << list;
        }

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

#endif// TRACKVIEW_H
