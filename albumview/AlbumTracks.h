#ifndef ALBUMTRACKS_H
#define ALBUMTRACKS_H

#include <QHBoxLayout>
#include <QWidget>

#include "AlbumCover.h"
#include "TracksListView.h"

class AlbumTracks : public QWidget
{
        Q_OBJECT

    public:
        AlbumTracks(QWidget* parent = 0);

    public slots:
        void onAlbumSelected(Album* album);

    signals:
        void coverClicked(Album* album);

    private:
        Album* m_album;

        AlbumCover* m_albumCover;
        QSpacerItem* m_lowerSpacer;
        QVBoxLayout* m_leftLayout;

        TracksListView* m_tracksListView;
        QHBoxLayout* m_layout;
};

#endif // ALBUMTRACKS_H
