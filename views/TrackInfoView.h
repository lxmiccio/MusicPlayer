#ifndef TRACKINFOVIEW_H
#define TRACKINFOVIEW_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "ElidedLabel.h"
#include "Track.h"

class TrackInfoView : public QWidget
{
    Q_OBJECT

    static const quint16 COVER_HEIGHT = 215;
    static const quint16 COVER_WIDTH = 175;
    static const quint16 IMAGE_HEIGHT = 175;
    static const quint16 IMAGE_WIDTH = 175;

public:
    explicit TrackInfoView(QWidget* parent = 0);

public slots:
    void changeTrack(Track* track);

private slots:
    void onTrackUpdated(Track* track, quint8 fields);
    void onAlbumUpdated(Album* album, quint8 fields);
    void onArtistUpdated(Artist* artist, quint8 fields);

private:
    Track* m_track;

    QLabel* m_cover;
    quint16 m_coverHeight;
    quint16 m_coverWidth;

    ElidedLabel* m_albumTitle;
    ElidedLabel* m_artistName;
    QLabel* m_lyrics;

    QVBoxLayout* m_layout;
};

#endif // TRACKINFOVIEW_H
