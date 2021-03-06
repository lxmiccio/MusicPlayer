#ifndef COVER_H
#define COVER_H

#include <QVBoxLayout>

#include "Album.h"
#include "Label.h"
#include "ClickableWidget.h"
#include "ElidedLabel.h"

class AlbumCover : public ClickableWidget
{
        Q_OBJECT

    public:
        explicit AlbumCover(Album* album, QWidget* parent = 0);
        explicit AlbumCover(QWidget* parent = 0);
        ~AlbumCover();

        const Album* album() const;
        void setAlbum(Album* album);

        static const quint16 COVER_HEIGHT = 215;
        static const quint16 COVER_WIDTH = 175;
        static const quint16 IMAGE_HEIGHT = 175;
        static const quint16 IMAGE_WIDTH = 175;

    signals:
        void coverClicked(Album* album);

    private slots:
        void onAlbumChanged();
        void onClicked();

    private:
        Album* m_album;

        QLabel* m_cover;
        ElidedLabel* m_albumTitle;
        ElidedLabel* m_artistName;

        QVBoxLayout* m_layout;
};

#endif // COVER_H
