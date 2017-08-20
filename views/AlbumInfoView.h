#ifndef ALBUMINFOVIEW_H
#define ALBUMINFOVIEW_H

#include <QHBoxLayout>
#include <QPointer>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "Label.h"
#include "ElidedLabel.h"
#include "LineWidget.h"
#include "TracksListView.h"

class AlbumInfoView : public QWidget
{
        Q_OBJECT

    public:
        explicit AlbumInfoView(QWidget* parent = 0);

        Album* album();
        QSize fittingSize();

    public slots:
        void changeAlbum(Album* album);

    private slots:
        void onAlbumUpdated(Album* album, quint8 fields);
        void onCoverClicked();

    signals:
        void coverClicked(Album* album);

    private:
        QPointer<Album> m_album;

        quint16 m_coverHeight;
        quint16 m_coverWidth;
        Label* m_cover;
        QSpacerItem* m_spacer;

        ElidedLabel* m_albumTitle;
        LineWidget* m_separator;
        TracksListView* m_tracksListView;

        QVBoxLayout* m_leftLayout;
        QVBoxLayout* m_rightLayout;
        QHBoxLayout* m_layout;
};

#endif // ALBUMINFOVIEW_H
