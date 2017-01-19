#include "Slider.h"

#include <QMouseEvent>

Slider::Slider(Qt::Orientation orientation, QWidget* parent) : QSlider(parent)
{
    m_acceptWheelEvents = false;
    m_lockScrubbing = false;
    m_scrubbing = false;

    setContextMenuPolicy(Qt::NoContextMenu);
    setOrientation(orientation);

    setStyleSheet("QSlider::groove:horizontal {"
                      "background: rgba(200, 200, 200, 50);"
                      "border-radius: 3px 3px 3px 3px;"
                      "margin-bottom: 0px;"
                      "margin-left: 0px;"
                      "margin-right: 0px;"
                      "margin-top: 0px;"
                  "}"
                  "QSlider::sub-page:horizontal {"
                      "background: white;"
                      "margin-bottom: 1px;"
                      "margin-left: 1px;"
                      "margin-right: 1px;"
                      "margin-top: 1px;"
                  "}");
}

void Slider::setAcceptWheelEvents(bool accept)
{
    m_acceptWheelEvents = accept;
}

void Slider::setLockScubbing(bool lock)
{
    m_lockScrubbing = lock;
}

void Slider::mouseMoveEvent(QMouseEvent* event)
{
    if(m_scrubbing)
    {
        if(m_lockScrubbing && event->pos().x() > width())
        {
            m_scrubbing = false;
        }
        QSlider::mouseMoveEvent(event);
    }
}

void Slider::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_scrubbing = true;
        QSlider::mousePressEvent(new QMouseEvent(QEvent::MouseButtonRelease, event->pos(), event->globalPos(), Qt::MidButton, Qt::MidButton, event->modifiers()));
    }
    else
    {
        QSlider::mousePressEvent(event);
    }
}

void Slider::wheelEvent(QWheelEvent* event)
{
    if(m_acceptWheelEvents)
    {
        QAbstractSlider::wheelEvent(event);
    }
    else
    {
        event->ignore();
    }
}
