#include "TrackSlider.h"

TrackSlider::TrackSlider(Qt::Orientation orientation, QWidget* parent) : Slider(orientation, parent)
{
    Slider::setLockScubbing(true);

    m_elapsedTime = 0;

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
    QObject::connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));

    setRange(0, 0);
    setValue(0);
}

TrackSlider::~TrackSlider()
{

}

void TrackSlider::onTrackStarted(int seconds)
{
    setRange(0, seconds * 1000);

    m_ignoreTimeout = true;
    m_time.start();
    m_timer.start(0);
}

void TrackSlider::onTrackFinished()
{
    setRange(0, 0);
    setValue(0);

    m_elapsedTime = 0;
    m_timer.stop();
}

void TrackSlider::onTrackPaused()
{
    m_elapsedTime += m_time.restart();
    m_timer.stop();
}

void TrackSlider::onTrackResumed()
{
    m_time.restart();
    m_timer.start();
}

void TrackSlider::onTimerTimeout()
{
    if(!m_ignoreTimeout)
    {
        m_elapsedTime += m_time.restart();

        blockSignals(true);
        QSlider::setValue(m_elapsedTime);
        blockSignals(false);
    }
}

void TrackSlider::onValueChanged(int value)
{
    m_elapsedTime = value;
    m_time.restart();
}

void TrackSlider::onPositionChanged(qint64 position)
{
    if(position > 0 && m_ignoreTimeout)
    {
        m_ignoreTimeout = false;
    }

    m_elapsedTime = position;

    blockSignals(true);
    QSlider::setValue(m_elapsedTime);
    blockSignals(false);

    m_time.restart();
}
