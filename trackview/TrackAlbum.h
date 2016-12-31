#ifndef TRACKALBUM_H
#define TRACKALBUM_H

#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"

class TrackAlbum : public QWidget
{
    public:
        explicit TrackAlbum(QWidget* parent = 0);
        ~TrackAlbum();

        void setAlbum(const Album* album);

        static const quint16 WIDGET_HEIGHT = 275;
        static const quint16 WIDGET_WIDTH = 200;

        static const quint16 IMAGE_HEIGHT = 200;
        static const quint16 IMAGE_WIDTH = 200;

    private:
        const Album* c_album;

        QLabel* m_cover;
        QSpacerItem* m_spacer1;
        QLabel* m_albumTitle;
        QSpacerItem* m_spacer2;
        QLabel* m_artistName;
        QSpacerItem* m_spacer3;
        QVBoxLayout* m_layout;
};

#endif // TRACKALBUM_H
