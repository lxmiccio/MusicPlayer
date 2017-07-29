#ifndef PLAYINGLYRICS_H
#define PLAYINGLYRICS_H

#include <QLabel>
#include <QWidget>

#include "ScrollableWidget.h"
#include "Track.h"

class PlayingLyrics : public ScrollableWidget
{
        Q_OBJECT

    public:
        PlayingLyrics(QWidget* parent = 0);
        ~PlayingLyrics();

    private slots:
        void onTrackStarted(Track* track);
        void onTrackUpdated(Track* track, quint8 fields);

    private:
        Track* m_track;
        QLabel* m_lyrics;
};

#endif// PLAYINGLYRICS_H
