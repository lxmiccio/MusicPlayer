#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QMutex>
#include <QMutexLocker>
#include <QSpacerItem>
#include <QSplitter>
#include <QVBoxLayout>

#include "ArtistAlbumsView.h"
#include "ArtistWidget.h"
#include "MusicLibrary.h"
#include "ScrollableWidget.h"

class ArtistView : public QWidget
{
        Q_OBJECT

    public:
        ArtistView(QWidget* parent = 0);
        ~ArtistView();

    signals:
        void coverClicked(Artist* artist);

    protected:
        void clearLayout(QLayout* layout);

    private:
        void repaintCovers();
        void repaintCoversAfterWidgetRemoved();

    private slots:
        void onAlbumAdded(Album* album);
        void onArtistWidgetClicked(ArtistWidget* widget);
        void onRemoveArtistWidgetClicked(ArtistWidget* widget);

    private:
        QMutex m_mutex;

        ArtistWidget* m_selectedArtistWidget;
        QVector<ArtistWidget*> m_artistWidgets;
        QVector<Artist*> m_artists;
        QVBoxLayout* m_layout;
        QSplitter* m_splitter;

        QVBoxLayout* m_leftLayout;
        ScrollableWidget* m_leftLayoutScrollable;

        ArtistAlbumsView* m_albumView;
        ScrollableWidget* m_albumViewScrollable;

        QSpacerItem* m_lowerSpacer;
        QSpacerItem* m_upperSpacer;
        QSpacerItem* m_middleVerticalSpacer;
};

#endif// ARTISTVIEW_H
