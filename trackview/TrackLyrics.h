#ifndef TRACKLYRICS_H
#define TRACKLYRICS_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "ScrollArea.h"
#include "Track.h"

class TrackLyrics : public QWidget
{
        Q_OBJECT

    public:
        TrackLyrics(QWidget* parent = 0);

    public slots:
        void onTrackStarted(const Track& track);

    private:
        const Track* c_track;

        QVBoxLayout* m_layout;
        ScrollArea* m_scrollArea;
        QLabel* m_lyrics;
};

#endif // TRACKLYRICS_H
