#ifndef TRACKINFOVIEW_H
#define TRACKINFOVIEW_H

#include <QPointer>
#include <QVBoxLayout>
#include <QWidget>

#include "ElidedLabel.h"
#include "Label.h"
#include "Track.h"

class TrackInfoView : public QWidget
{
        Q_OBJECT

    public:
        explicit TrackInfoView(QWidget* parent = 0);

    public slots:
        void changeTrack(Track* track);

    private slots:
        void onTrackUpdated(Track* track, quint8 fields);
        void onAlbumUpdated(Album* album, quint8 fields);
        void onArtistUpdated(Artist* artist, quint8 fields);

    private:
        QPointer<Track> m_track; /* Use QPointer so that the pointer will result NULL if deleted by another object */

        quint16 m_coverHeight;
        quint16 m_coverWidth;
        Label* m_cover;

        ElidedLabel* m_albumTitle;
        ElidedLabel* m_artistName;
        QLabel* m_lyrics;

        QVBoxLayout* m_layout;
};

#endif // TRACKINFOVIEW_H
