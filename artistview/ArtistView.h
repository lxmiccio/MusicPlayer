#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QHBoxLayout>
#include <QMutex>
#include <QMutexLocker>
#include <QSpacerItem>
#include <QSplitter>

#include "ArtistAlbumsView.h"
#include "ArtistsListView.h"
#include "ScrollableWidget.h"

class ArtistView : public QWidget
{
        Q_OBJECT

    public:
        ArtistView(QWidget* parent = 0);
        ~ArtistView();

    private slots:
        void onArtistAdded(Artist* artist);
        void onArtistDestroyed(QObject* artist);

    private:
        QMutex m_mutex;

        ArtistsListView* m_artistsListView;
        ArtistAlbumsView* m_artistAlbumsView;
        ScrollableWidget* m_scrollableWidget;
        QSplitter* m_splitter;

        QHBoxLayout* m_layout;
};

#endif// ARTISTVIEW_H
