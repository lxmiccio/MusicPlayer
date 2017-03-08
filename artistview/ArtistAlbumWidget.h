#ifndef ARTISTALBUMWIDGET_H
#define ARTISTALBUMWIDGET_H

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "ElidedLabel.h"

#include "TrackItem.h"
#include "TrackList.h"
#include "TrackModel.h"
#include "TrackDelegate.h"

class ArtistAlbumWidget : public QWidget
{
    public:
        ArtistAlbumWidget(QWidget* parent = 0);
        void setAlbum(Album* album);

    private:
        void clear();

    private:
        Album* m_album;
        QLabel* m_cover;
        ElidedLabel* m_albumTitle;

        QVector<TrackItem*> m_items;
        TrackList* m_trackList;
        TrackModel* m_model;
        TrackDelegate* m_delegate;

        QVBoxLayout* m_layout;
        QHBoxLayout* m_upperLayout;
};

#endif // ARTISTALBUMWIDGET_H
