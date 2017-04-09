#ifndef PLAYINGVIEW_H
#define PLAYINGVIEW_H

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "BackgroundWidget.h"
#include "Playlist.h"
#include "Track.h"
#include "PlayingAlbum.h"
#include "TrackDelegate.h"
#include "TrackItem.h"
#include "TrackView.h"
#include "PlayingLyrics.h"
#include "TrackModel.h"

class TrackDelegate;
class TrackItem;
class TrackView;
class TrackModel;

class PlayingView : public QWidget
{
        Q_OBJECT

    public:
        explicit PlayingView(quint8 mode, QWidget* parent = 0);
        ~PlayingView();

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

        PlayingAlbum* m_playingAlbum;
        PlayingLyrics* m_playingLyrics;

        QSpacerItem* m_spacer;

        TrackView* m_trackView;
        ScrollableArea* m_scrollableArea;

        QVector<TrackItem*> m_items;

        QVBoxLayout* m_leftLayout;
        QHBoxLayout* m_layout;

        quint8 m_mode;
};

#endif // PLAYINGVIEW_H
