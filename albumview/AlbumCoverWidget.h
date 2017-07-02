#ifndef ALBUMCOVERWIDGET_H
#define ALBUMCOVERWIDGET_H

#include <QVBoxLayout>

#include "Album.h"
#include "ClickableLabel.h"
#include "ClickableWidget.h"
#include "ElidedLabel.h"

class AlbumCoverWidget : public ClickableWidget
{
        Q_OBJECT

    public:
        static const quint8 TOP = 1;
        static const quint8 RIGHT = 2;
        static const quint8 BOTTOM = 4;
        static const quint8 LEFT = 8;
        static const quint8 CENTER = 16;

        explicit AlbumCoverWidget(Album* album, QWidget* parent = 0);
        explicit AlbumCoverWidget(QWidget* parent = 0);
        ~AlbumCoverWidget();

        Album* album() const;
        void setAlbum(Album* album);

        quint8 position();
        void setPosition(quint8 position);

        quint8 margin();
        void setMargin(quint8 margin);

        static const quint16 COVER_HEIGHT = 215;
        static const quint16 COVER_WIDTH = 175;
        static const quint16 IMAGE_HEIGHT = 175;
        static const quint16 IMAGE_WIDTH = 175;

    signals:
        void coverClicked(Album* album);

    private slots:
        void onAlbumChanged(Album* album, quint8 fields);
        void onClicked();

    private:
        Album* m_album;

        QLabel* m_cover;
        ElidedLabel* m_albumTitle;
        ElidedLabel* m_artistName;
        QVBoxLayout* m_layout;
};

#endif // ALBUMCOVERWIDGET_H
