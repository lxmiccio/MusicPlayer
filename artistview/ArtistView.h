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
#include "ScrollableArea.h"

class ArtistView : public QWidget
{
        Q_OBJECT

    public:
        ArtistView(QWidget* parent = 0);
        ~ArtistView();

    signals:
        void coverClicked(const Artist* artist);

    protected:
        void clearLayout(QLayout* layout);

    private:
        void repaintCovers();
        void repaintCoversAfterWidgetRemoved();

    private slots:
        void onAlbumAdded(const Album* album);
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
        ScrollableArea* m_leftLayoutScrollable;
        TrackLoader* m_trackLoader;

        ArtistAlbumsView* m_albumView;
        ScrollableArea* m_albumViewScrollable;

        QSpacerItem* m_lowerSpacer;
        QSpacerItem* m_upperSpacer;
        QSpacerItem* m_middleVerticalSpacer;
};

#endif // ARTISTVIEW_H
