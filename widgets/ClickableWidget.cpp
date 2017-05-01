#include "ClickableWidget.h"

#include "ImageUtils.h"

ClickableWidget::ClickableWidget(QWidget* parent) : BackgroundWidget(parent)
{
}

void ClickableWidget::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);

    if(!m_moved)
    {
        m_dragPoint = event->pos();
        m_pressed = true;
        m_time.start();
    }
}

void ClickableWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);

    if(!m_moved && m_time.elapsed() < qApp->doubleClickInterval())
    {
        if(event->button() == Qt::LeftButton)
        {
            emit leftButtonClicked();
        }

        if(event->button() == Qt::RightButton)
        {
            emit rightButtonClicked();
        }
    }

    m_moved = false;
    m_pressed = false;
}
