#ifndef TRACKTABLEVIEW_H
#define TRACKTABLEVIEW_H

#include <QHeaderView>
#include <QTableView>

#include "TrackDelegate.h"
#include "TrackModel.h"
#include "TrackView.h"

class TrackList : public QTableView
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

        explicit TrackList(quint8 mode, QWidget* parent = 0);
        ~TrackList();

        QSize fittingSize();
        quint8 mode() const;

        int rowCount() const;
        int columnCount() const;
        void propendItem(const Track* track);
        void insertItemAt(const Track* track, int row);
        void removeFirstItem();
        void removeLastItem();
        void removeItemAt(int row);
        void clear();

    public slots:
        void appendItem(const Track* track);
        void removeItem(const Track* track);

    protected:
        virtual void resizeEvent(QResizeEvent* event);
        virtual QSize sizeHint();

    private:
        quint8 m_mode;
};

#endif // TRACKTABLEVIEW_H
