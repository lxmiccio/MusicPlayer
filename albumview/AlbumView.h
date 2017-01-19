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
        void onTrackAdded(const Track& track);

    signals:
        void coverClicked(const Album& album);

    private slots:
        void onCoverClicked(const Album& album);

    private:
        QVector<const Album*> m_albums;

        void clearLayout(QLayout* layout);
        void displayCover(Cover* cover);

        quint8 albumsPerRow(quint16 width);
        quint8 spacerWidth(quint16 width);

        QVector<Cover*> m_covers;
        QVector<QHBoxLayout*> m_layouts;
        QVBoxLayout* m_layout;

        QSpacerItem* m_upperSpacer;
        QSpacerItem* m_leftSpacer;
        QSpacerItem* m_lowerSpacer;
        QSpacerItem* m_rightSpacer;
        QSpacerItem* m_middleHorizontalSpacer;
        QSpacerItem* m_middleVerticalSpacer;

        quint8 m_currentColumn;
        quint8 m_currentRow;

        quint8 m_albumCurrentColumn;
        quint8 m_albumsPerRow;
};

#endif // ALBUMVIEW_H
