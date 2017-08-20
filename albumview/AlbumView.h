#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "AlbumGrid.h"
#include "AlbumInfoView.h"
#include "AlbumTracks.h"
#include "AlbumCover.h"
#include "ScrollableWidget.h"

class AlbumView : public ScrollableWidget
{
        Q_OBJECT

    public:
        explicit AlbumView(QWidget* parent = 0);
        ~AlbumView();

    private slots:
        void onAlbumGridCoverClicked(Album* album);
        void onAlbumTracksCoverClicked(Album* album);

    private:
        AlbumGrid* m_albumGrid;
        AlbumInfoView* m_albumInfo;
        AlbumTracks* m_albumTracks;
        QVBoxLayout* m_layout;
};

#endif // ALBUMVIEW_H
