#ifndef ARTISTALBUMSVIEW_H
#define ARTISTALBUMSVIEW_H

#include <QMutex>
#include <QMutexLocker>
#include <QVBoxLayout>
#include <QWidget>

#include "Artist.h"
#include "ArtistAlbumWidget.h"
#include "Line.h"

class ArtistAlbumsView : public QWidget
{
        Q_OBJECT

    public:
        ArtistAlbumsView(QWidget* parent = 0);
        ~ArtistAlbumsView();

        const Artist* artist() const;
        void clearLayout(QLayout* layout);

    public slots:
        void onArtistChanged(const Artist* artist);

    private:
        const Artist* c_artist;
        QMutex m_mutex;
        QVector<ArtistAlbumWidget*> m_widgets;
        QVector<Line*> m_lines;
        QVBoxLayout* m_layout;
};

#endif // ARTISTALBUMSVIEW_H
