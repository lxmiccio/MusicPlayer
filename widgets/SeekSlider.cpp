#include "SeekSlider.h"

#include <QMouseEvent>

SeekSlider::SeekSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(parent)
{
    m_acceptWheelEvents = false;
    m_lockScrubbing = false;
    m_scrubbing = false;
    m_timeLine = NULL;

    setOrientation(orientation);

    setStyleSheet(QString("QSlider::groove:horizontal {"
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
                          "}"));
}

void SeekSlider::setAcceptWheelEvents(bool accept)
{
    m_acceptWheelEvents = accept;
}

void SeekSlider::setLockScubbing(bool lock)
{
    m_lockScrubbing = lock;
}

void SeekSlider::setTimeLine(QTimeLine *timeline)
{
    m_timeLine = timeline;
}
#include <QDebug>
void SeekSlider::setValue(int value)
{
    if(m_timeLine && sender() == m_timeLine)
    {
        qDebug() << "time";
        blockSignals(true);
        QSlider::setValue(value);
        blockSignals(false);
    }
    else
    {
        qDebug() << "notime";
        QSlider::setValue(value);
    }
}

void SeekSlider::mouseMoveEvent(QMouseEvent* event)
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

void SeekSlider::mousePressEvent(QMouseEvent* event)
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

void SeekSlider::wheelEvent(QWheelEvent* event)
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
