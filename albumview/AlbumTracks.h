#ifndef ALBUMTRACKS_H
#define ALBUMTRACKS_H

#include <QHBoxLayout>
#include <QWidget>

#include "Album.h"
#include "Playlist.h"
#include "Track.h"
#include "TrackView.h"

class AlbumTracks : public QWidget
{
        Q_OBJECT

    public:
        AlbumTracks(QWidget* parent = 0);

    public slots:
        void onAlbumSelected(Album* album);

    signals:
        void coverClicked(Album* album);
        void playlistSelected(Playlist* playlist);

    private slots:
        void onTrackSelected(Track* track);

    private:
        Album* m_album;

        AlbumCover* m_albumCover;
        QSpacerItem* m_lowerSpacer;
        QVBoxLayout* m_leftLayout;

        TrackView* m_trackView;
        QHBoxLayout* m_layout;
};

#endif // ALBUMTRACKS_H
