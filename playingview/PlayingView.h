#ifndef PLAYINGVIEW_H
#define PLAYINGVIEW_H

#include <QHeaderView>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QScrollBar>
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "BackgroundWidget.h"
#include "ImageUtils.h"
#include "Playlist.h"
#include "Track.h"
#include "PlayingAlbum.h"
#include "TracksListView.h"
#include "PlayingLyrics.h"

class PlayingView : public QWidget
{
        Q_OBJECT

    public:
        explicit PlayingView(quint8 mode, QWidget* parent = 0);
        ~PlayingView();

        static const quint16 WIDGET_HEIGHT = 415;

    public slots:
        void onAlbumSelected(Album* album);
        void onPlaylistSelected(Playlist* playlist);

    signals:
        void doubleClicked(Track* track);
        void coverClicked();

    private slots:
        void onDoubleClicked(const QModelIndex& index);
        void onCoverClicked();

    private:
        void clear();

        PlayingAlbum* m_playingAlbum;
        PlayingLyrics* m_playingLyrics;

        QSpacerItem* m_spacer;

        TracksListView* m_tracksListView;
        ScrollableWidget* m_scrollableWidget;

        QVector<TracksListItem*> m_items;

        QVBoxLayout* m_leftLayout;
        QHBoxLayout* m_layout;

        quint8 m_mode;
};

#endif// PLAYINGVIEW_H
