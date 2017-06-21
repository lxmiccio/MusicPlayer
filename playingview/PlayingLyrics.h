#ifndef PLAYINGLYRICS_H
#define PLAYINGLYRICS_H

#include <QLabel>
#include <QWidget>

#include "ScrollableArea.h"
#include "Track.h"

class PlayingLyrics : public ScrollableArea
{
        Q_OBJECT

    public:
        PlayingLyrics(QWidget* parent = 0);
        ~PlayingLyrics();

    private slots:
        void onTrackStarted(Track* track);
        void onTrackUpdated(Track* track, quint8 fields);

    private:
        Track* c_track;
        QLabel* m_lyrics;
};

#endif// PLAYINGLYRICS_H
