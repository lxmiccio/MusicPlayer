#ifndef ALBUMINFOVIEW_H
#define ALBUMINFOVIEW_H

#include <QLabel>
#include <QPointer>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "ElidedLabel.h"

class AlbumInfoView : public QWidget
{
        Q_OBJECT

    public:
        explicit AlbumInfoView(QWidget* parent = 0);

    public slots:
        void changeAlbum(Album* album);

    private slots:
        void onAlbumUpdated(Album* album, quint8 fields);

    private:
        QPointer<Album> m_album;

        QLabel* m_cover;
        quint16 m_coverHeight;
        quint16 m_coverWidth;

        ElidedLabel* m_albumTitle;

        QVBoxLayout* m_layout;
};

#endif // ALBUMINFOVIEW_H
