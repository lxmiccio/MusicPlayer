#include "ClickableLabel.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

ClickableLabel::ClickableLabel(QWidget* parent) : QLabel(parent), m_opacity(0.5), m_moved(false), m_pressed(false)
{
    QLabel::setCursor(Qt::PointingHandCursor);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::setOpacity(float opacity)
{
    m_opacity = opacity;

    repaint();
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    QLabel::mousePressEvent(event);

    if (!m_moved)
    {
        m_dragPoint = event->pos();
        m_pressed = true;
        m_time.start();
    }
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* event)
{
    QLabel::mouseReleaseEvent(event);

    if(!m_moved && m_time.elapsed() < qApp->doubleClickInterval() && event->button() == Qt::LeftButton)
        emit clicked();

    m_moved = false;
    m_pressed = false;
}

void ClickableLabel::mouseMoveEvent(QMouseEvent* event)
{
    if(m_pressed)
    {
        QPoint delta = m_dragPoint - event->pos();

        if(qAbs(delta.y()) > 3)
        {
            m_moved = true;

            emit resized(delta);
        }
    }
}

void ClickableLabel::paintEvent(QPaintEvent*  event)
{
    QPainter painter(this);
    painter.setOpacity(m_opacity);
    painter.setRenderHint(QPainter::TextAntialiasing);

    const QString elidedText = fontMetrics().elidedText(text(), Qt::ElideRight, contentsRect().width());
    painter.drawText(contentsRect(), alignment(), elidedText);

    QLabel::paintEvent(event);
}
