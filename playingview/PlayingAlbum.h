#ifndef PLAYINGALBUM_H
#define PLAYINGALBUM_H

#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "ClickableLabel.h"
#include "Cover.h"

class PlayingAlbum : public QWidget
{
        Q_OBJECT

    public:
        explicit PlayingAlbum(QWidget* parent = 0);
        ~PlayingAlbum();

        void setAlbum(const Album* album);

        static const quint16 WIDGET_HEIGHT = 200;
        static const quint16 WIDGET_WIDTH = 300;
        static const quint16 IMAGE_HEIGHT = 175;
        static const quint16 IMAGE_WIDTH = 175;

    signals:
        void coverClicked();

    private:
        const Album* c_album;

        ClickableLabel* m_cover;
        QSpacerItem* m_spacer1;
        QLabel* m_artistName;
        QSpacerItem* m_spacer2;
        QLabel* m_albumTitle;
        QSpacerItem* m_spacer3;
        QVBoxLayout* m_layout;
};

#endif // PLAYINGALBUM_H
