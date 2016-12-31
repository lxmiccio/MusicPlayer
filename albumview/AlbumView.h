#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include <QHBoxLayout>
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

        QVector<Cover*> m_covers;
        QVector<QHBoxLayout*> m_layouts;
        QVBoxLayout* m_layout;

        quint8 m_currentColumn;
        quint8 m_currentRow;
        quint8 m_albumsPerRow;
};

#endif // ALBUMVIEW_H
