#ifndef ARTISTALBUMSVIEW_H
#define ARTISTALBUMSVIEW_H

#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QVBoxLayout>
#include <QWidget>

#include "AlbumInfoView.h"
#include "Artist.h"
#include "LineWidget.h"

class ArtistAlbumsView : public QWidget
{
        Q_OBJECT

    public:
        ArtistAlbumsView(QWidget* parent = 0);
        ~ArtistAlbumsView();

        Artist* artist() const;

    public slots:
        void onArtistChanged(Artist* artist);

    private slots:
        void onAlbumAdded(Album* album);
        void onAlbumRemoved(Album* album);

    private:
        void clearLayout(QLayout* layout);
        qint16 widgetIndex(Album* album);

        QPointer<Artist> m_artist;
        QMutex m_mutex;

        QVector<AlbumInfoView*> m_widgets;
        QVector<LineWidget*> m_separators;
        QVBoxLayout* m_layout;
};

#endif// ARTISTALBUMSVIEW_H
