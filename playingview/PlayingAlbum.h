#ifndef PLAYINGALBUM_H
#define PLAYINGALBUM_H

#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "AlbumCover.h"
#include "ClickableWidget.h"

class PlayingAlbum : public ClickableWidget
{
        Q_OBJECT

    public:
        explicit PlayingAlbum(QWidget* parent = 0);
        ~PlayingAlbum();

        void setAlbum(Album* album);

        static const quint16 WIDGET_HEIGHT = 200;
        static const quint16 WIDGET_WIDTH = 300;
        static const quint16 IMAGE_HEIGHT = 175;
        static const quint16 IMAGE_WIDTH = 175;

    private:
        Album* c_album;

        QLabel* m_cover;
        QSpacerItem* m_spacer1;
        QLabel* m_artistName;
        QSpacerItem* m_spacer2;
        QLabel* m_albumTitle;
        QSpacerItem* m_spacer3;
        QVBoxLayout* m_layout;
};

#endif // PLAYINGALBUM_H
