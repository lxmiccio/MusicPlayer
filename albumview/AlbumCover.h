#ifndef COVER_H
#define COVER_H

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "AlbumCoverWidget.h"

class AlbumCover : public QWidget
{
        Q_OBJECT

    public:
        static const quint8 TOP = 1;
        static const quint8 RIGHT = 2;
        static const quint8 BOTTOM = 4;
        static const quint8 LEFT = 8;
        static const quint8 CENTER = 16;

        explicit AlbumCover(Album* album, QWidget* parent = 0);
        explicit AlbumCover(QWidget* parent = 0);
        ~AlbumCover();

        Album* album() const;
        void setAlbum(Album* album);

        quint8 position();
        void setPosition(quint8 position);

        quint8 margin();
        void setMargin(quint8 margin);

    signals:
        void coverClicked(Album* album);

    private:
        quint8 m_margin;
        quint8 m_position;

        AlbumCoverWidget* m_albumCoverWidget;

        QSpacerItem* m_topSpacer;
        QSpacerItem* m_rightSpacer;
        QSpacerItem* m_bottomSpacer;
        QSpacerItem* m_leftSpacer;

        QVBoxLayout* m_verticalLayout;
        QHBoxLayout* m_layout;
};

#endif// COVER_H
