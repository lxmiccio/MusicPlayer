#ifndef PLAYINGLYRICS_H
#define PLAYINGLYRICS_H

#include <QLabel>
#include <QScrollBar>
#include <QWidget>

#include "ScrollableArea.h"
#include "Track.h"

class PlayingLyrics : public ScrollableArea
{
        Q_OBJECT

    public:
        PlayingLyrics(QWidget* parent = 0);

    public slots:
        void onTrackStarted(const Track* track);

    private:
        const Track* c_track;
        QLabel* m_lyrics;
};

#endif // PLAYINGLYRICS_H
