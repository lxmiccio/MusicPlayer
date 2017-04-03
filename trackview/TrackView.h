#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "BackgroundWidget.h"
#include "Playlist.h"
#include "Track.h"
#include "TrackAlbum.h"
#include "TrackDelegate.h"
#include "TrackItem.h"
#include "TrackList.h"
#include "TrackLyrics.h"
#include "TrackModel.h"

class TrackDelegate;
class TrackItem;
class TrackList;
class TrackModel;

class TrackView : public QWidget
{
        Q_OBJECT

    public:
        explicit TrackView(quint8 mode, QWidget* parent = 0);
        ~TrackView();

        static const quint8 TRACK = 1;
        static const quint8 TITLE = 2;
        static const quint8 ALBUM = 4;
        static const quint8 ARTIST = 8;
        static const quint8 DURATION = 16;

        static const quint8 FULL = TRACK | TITLE | ALBUM | ARTIST | DURATION;
        static const quint8 REDUCED = TRACK | TITLE | DURATION;

        static const quint16 WIDGET_HEIGHT = 415;

    public slots:
        void onAlbumSelected(const Album& album);
        void onPlaylistSelected(const Playlist* playlist);
        void onTrackStarted(const Track& track);

    signals:
        void doubleClicked(const Track&);
        void coverClicked();
        void trackStarted(const Track&);

    private slots:
        void onDoubleClicked(const QModelIndex& index);
        void onCoverClicked();

    private:
        void clear();

        TrackAlbum* m_trackAlbum;
        TrackLyrics* m_trackLyrics;

        QSpacerItem* m_spacer;

        TrackList* m_trackList;

        QVector<TrackItem*> m_items;

        QVBoxLayout* m_leftLayout;
        QHBoxLayout* m_layout;

        quint8 m_mode;
};

#endif // TRACKVIEW_H
