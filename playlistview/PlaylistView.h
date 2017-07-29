#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QHBoxLayout>
#include <QWidget>

#include "Playlist.h"
#include "ScrollableWidget.h"
#include "TrackInfoView.h"
#include "TracksListView.h"

class PlaylistView : public QWidget
{
    public:
        explicit PlaylistView(QWidget* parent = 0);

    public slots:
        void changePlaylist(const QString& name);
        void changePlaylist(Playlist* playlist);

    private:
        Playlist* m_playlist;

        TrackInfoView* m_trackInfoView;
        TracksListView* m_tracksListView;
        ScrollableWidget* m_trackListScrollable;
        QHBoxLayout* m_layout;
};

#endif // PLAYLISTVIEW_H
