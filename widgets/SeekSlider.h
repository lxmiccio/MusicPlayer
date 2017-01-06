#ifndef SEEKSLIDER_H
#define SEEKSLIDER_H

#include <QTime>
#include <QTimer>

#include "Slider.h"

class SeekSlider : public Slider
{
    Q_OBJECT

    public:
        SeekSlider(Qt::Orientation orientation, QWidget* parent = 0);

    public slots:
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

#endif // SEEKSLIDER_H
