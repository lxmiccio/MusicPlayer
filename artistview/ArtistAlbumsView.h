#ifndef ARTISTALBUMSVIEW_H
#define ARTISTALBUMSVIEW_H

#include <QMutex>
#include <QMutexLocker>
#include <QVBoxLayout>
#include <QWidget>

#include "Artist.h"
#include "ArtistAlbumWidget.h"
#include "HorizontalLine.h"

class ArtistAlbumsView : public QWidget
{
        Q_OBJECT

    public:
        ArtistAlbumsView(QWidget* parent = 0);
        void clearLayout(QLayout* layout);

    public slots:
        void onArtistChanged(const Artist* artist);

    private:
        QMutex m_mutex;
        QVector<ArtistAlbumWidget*> m_widgets;
        QVector<HorizontalLine*> m_horizontalLines;
        QVBoxLayout* m_layout;
};

#endif // ARTISTALBUMSVIEW_H
