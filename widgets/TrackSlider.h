#ifndef TRACKSLIDER_H
#define TRACKSLIDER_H

#include <QTime>
#include <QTimer>

#include "Slider.h"

class TrackSlider : public Slider
{
        Q_OBJECT

    public:
        explicit TrackSlider(Qt::Orientation orientation, QWidget* parent = 0);
        ~TrackSlider();

    public slots:
        void onPositionChanged(qint64 position);
        void onTrackStarted(int seconds);
        void onTrackFinished();
        void onTrackPaused();
        void onTrackResumed();

    private slots:
        void onTimerTimeout();
        void onValueChanged(int value);

    private:
        quint64 m_elapsedTime;
        bool m_ignoreTimeout;

        QTime m_time;
        QTimer m_timer;
};

#endif// TRACKSLIDER_H
