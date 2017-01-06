#ifndef TRACKSLIDER_H
#define TRACKSLIDER_H

#include <QTime>
#include <QTimer>

#include "Slider.h"

class TrackSlider : public Slider
{
    Q_OBJECT

    public:
        TrackSlider(Qt::Orientation orientation, QWidget* parent = 0);

    public slots:
        void onPositionChanged(qint64 position);
        void onTrackStarted(int duration);
        void onTrackFinished();
        void onTrackPaused();
        void onTrackResumed();

    private slots:
        void onTimerTimeout();
        void onValueChanged(int value);

    private:
        quint64 m_elapsedTime;
        QTime* m_time;
        QTimer* m_timer;
};

#endif // TRACKSLIDER_H
