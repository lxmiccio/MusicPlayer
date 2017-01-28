#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include <QHBoxLayout>
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

    private:
        void repaintCovers();

    private slots:
        void onAlbumAdded(const Album* album);
        void onCoverClicked(const Album& album);

    private:
        QVector<const Album*> m_albums;

        void clearLayout(QLayout* layout);

        quint8 albumsPerRow(quint16 width);
        quint8 horizontalSpacerWidth(quint16 width);

        QVector<Cover*> m_covers;
        QVector<QHBoxLayout*> m_layouts;
        QVBoxLayout* m_layout;

        QSpacerItem* m_upperSpacer;
        QSpacerItem* m_leftSpacer;
        QSpacerItem* m_lowerSpacer;
        QSpacerItem* m_rightSpacer;
        QSpacerItem* m_middleHorizontalSpacer;
        QSpacerItem* m_middleVerticalSpacer;

        quint8 m_currentColumn; /* Columns including spacer */
        quint8 m_currentRow; /* Rows including spacer */

        quint8 m_albumCurrentColumn; /* Columns excluding spacer */
        quint8 m_albumsPerRow;
};

#endif // ALBUMVIEW_H
