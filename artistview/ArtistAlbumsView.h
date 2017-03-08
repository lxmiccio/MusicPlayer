#ifndef ARTISTALBUMSVIEW_H
#define ARTISTALBUMSVIEW_H

#include <QVBoxLayout>
#include <QWidget>

#include "Artist.h"
#include "ArtistAlbumWidget.h"

class ArtistAlbumsView : public QWidget
{
    public:
        ArtistAlbumsView(QWidget* parent = 0);

    public slots:
        onArtistChanged(Artist* artist);

    private:
        QVector<ArtistAlbumWidget*> m_widgets;
        QVBoxLayout* m_layout;
};

#endif // ARTISTALBUMSVIEW_H
