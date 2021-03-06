#ifndef ALBUMGRID_H
#define ALBUMGRID_H

#include <QHBoxLayout>
#include <QMutex>
#include <QMutexLocker>
#include <QResizeEvent>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "AlbumCover.h"
#include "ScrollableWidget.h"

class AlbumGrid : public ScrollableWidget
{
        Q_OBJECT

    public:
        explicit AlbumGrid(QWidget* parent = 0);
        ~AlbumGrid();

    signals:
        void coverClicked(Album* album);

    protected:
        virtual void resizeEvent(QResizeEvent* event);

        void clearLayout(QLayout* layout);
        void sort();

        quint8 albumsPerRow(quint16 width);
        quint8 horizontalSpacerWidth(quint16 width);

    private:
        void repaintCovers();

    private slots:
        void onAlbumAdded(Album* album);
        void onCoverClicked(Album* album);

    private:
        QMutex m_mutex;

        QVector<AlbumCover*> m_albumCovers;
        QVector<QHBoxLayout*> m_layouts;
        QVBoxLayout* m_layout;
        QWidget* m_widget;

        QSpacerItem* m_leftSpacer;
        QSpacerItem* m_lowerSpacer;
        QSpacerItem* m_rightSpacer;
        QSpacerItem* m_upperSpacer;
        QSpacerItem* m_middleHorizontalSpacer; /* Spacer between albums */
        QSpacerItem* m_middleVerticalSpacer; /* Spacer between horizontal layouts */

        quint8 m_albumsCurrentColumn; /* Column index excluding spacer */
        quint8 m_albumsPerRow; /* Number of albums for each rows */

        quint8 m_currentColumn; /* Column index including spacer */
        quint8 m_currentRow; /* Row index including spacer */
};

#endif // ALBUMGRID_H
