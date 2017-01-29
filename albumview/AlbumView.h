#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include <QHBoxLayout>
#include <QMutex>
#include <QMutexLocker>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "Album.h"
#include "BackgroundWidget.h"
#include "Cover.h"

class AlbumView : public QWidget
{
        Q_OBJECT

    public:
        explicit AlbumView(QWidget* parent = 0);
        ~AlbumView();

    public slots:
        void onScrollAreaResized(QResizeEvent* event);

    signals:
        void coverClicked(const Album& album);

    protected:
        void clearLayout(QLayout* layout);
        quint8 albumsPerRow(quint16 width);
        quint8 horizontalSpacerWidth(quint16 width);

    private:
        void repaintCovers();

    private slots:
        void onAlbumAdded(const Album* album);
        void onCoverClicked(const Album& album);

    private:
        QMutex m_mutex;

        QVector<Cover*> m_covers;
        QVector<QHBoxLayout*> m_layouts;
        QVBoxLayout* m_layout;

        QSpacerItem* m_leftSpacer;
        QSpacerItem* m_lowerSpacer;
        QSpacerItem* m_rightSpacer;
        QSpacerItem* m_upperSpacer;
        QSpacerItem* m_middleHorizontalSpacer; /* Spacer between albums */
        QSpacerItem* m_middleVerticalSpacer; /* Spacer between horizontal layouts */

        quint8 m_currentColumn; /* Column index including spacer */
        quint8 m_currentRow; /* Row index including spacer */

        quint8 m_albumCurrentColumn; /* Column index excluding spacer */
        quint8 m_albumsPerRow; /* Maximum album for each rows */
};

#endif // ALBUMVIEW_H
