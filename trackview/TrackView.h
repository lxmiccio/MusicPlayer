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

class TrackView : public QWidget
{
        Q_OBJECT

    public:
        explicit TrackView(QWidget* parent = 0);
        ~TrackView();

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
        TrackModel* m_model;
        TrackDelegate* m_delegate;

        QVector<TrackItem*> m_items;

        QVBoxLayout* m_leftLayout;
        QHBoxLayout* m_layout;
};

#endif // TRACKVIEW_H
