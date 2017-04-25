#ifndef ARTISTALBUMSVIEW_H
#define ARTISTALBUMSVIEW_H

#include <QMutex>
#include <QMutexLocker>
#include <QVBoxLayout>
#include <QWidget>

#include "Artist.h"
#include "ArtistAlbumWidget.h"
#include "LineWidget.h"

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

    private slots:
        void onAlbumAdded(Album* album);
        void onAlbumUpdated(Album* album);
        void onAlbumRemoved(Album* album);

    private:
        qint16 widgetIndex(Album* album);

        const Artist* m_artist;
        QMutex m_mutex;

        QVector<ArtistAlbumWidget*> m_widgets;
        QVector<LineWidget*> m_lineWidgets;
        QVBoxLayout* m_layout;
};

#endif // ARTISTALBUMSVIEW_H
