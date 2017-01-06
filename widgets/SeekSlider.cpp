#include "SeekSlider.h"

#include <QMouseEvent>

SeekSlider::SeekSlider(Qt::Orientation orientation, QWidget* parent) : Slider(orientation, parent)
{
    m_elapsedTime = 0;

    m_time = new QTime();

    m_timer = new QTimer();
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));

    QObject::connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
}

void SeekSlider::onTrackStarted(int duration)
{
    setRange(0, duration * 1000);

    m_time->start();
    m_timer->start(25);
}

void SeekSlider::onTrackFinished()
{
    setValue(0);

    m_elapsedTime = 0;
    m_timer->stop();
}

void SeekSlider::onTrackPaused()
{
    m_elapsedTime += m_time->restart();
    m_timer->stop();
}

void SeekSlider::onTrackResumed()
{
    m_time->restart();
    m_timer->start();
}

void SeekSlider::onTimerTimeout()
{
    m_elapsedTime += m_time->restart();

    blockSignals(true);
    QSlider::setValue(m_elapsedTime);
    blockSignals(false);
}

void SeekSlider::onValueChanged(int value)
{
    m_timer->stop();

    m_elapsedTime = value;
    m_time->restart();
    m_timer->start();
}
