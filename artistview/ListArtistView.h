#ifndef LISTARTISTVIEW_H
#define LISTARTISTVIEW_H

#include <QHBoxLayout>
#include <QMutex>
#include <QMutexLocker>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "ArtistAlbumsView.h"
#include "ArtistWidget.h"
#include "MusicLibrary.h"

class ListArtistView : public QWidget
{
        Q_OBJECT

    public:
        ListArtistView(QWidget* parent = 0);
        ~ListArtistView();

    public slots:
        void onScrollAreaResized(QResizeEvent* event);

    signals:
        void coverClicked(const Artist& artist);

    protected:
        void clearLayout(QLayout* layout);

    private:
        void repaintCovers();

    private slots:
        void onAlbumAdded(const Album* album);
        void onCoverClicked(const Artist& artist);

    private:
        QMutex m_mutex;

        QVector<ArtistWidget*> m_artistWidgets;
        QVector<Artist*> m_artists;
        QVBoxLayout* m_layout;

        ArtistAlbumsView* m_albumView;

        QSpacerItem* m_lowerSpacer;
        QSpacerItem* m_upperSpacer;
        QSpacerItem* m_middleVerticalSpacer;
};

#endif // LISTARTISTVIEW_H
