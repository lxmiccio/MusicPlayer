#ifndef TRACKLYRICS_H
#define TRACKLYRICS_H

#include <QLabel>
#include <QScrollBar>
#include <QWidget>

#include "AudioEngine.h"
#include "GuiUtils.h"
#include "ScrollableArea.h"
#include "Track.h"
#include "TrackAlbum.h"

class TrackLyrics : public ScrollableArea
{
        Q_OBJECT

    public:
        TrackLyrics(QWidget* parent = 0);

    public slots:
        void onTrackStarted(const Track* track);

    private:
        const Track* c_track;
        QLabel* m_lyrics;
};

#endif // TRACKLYRICS_H
