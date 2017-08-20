#include "Label.h"

Label::Label(QWidget* parent) : QLabel(parent), m_opacity(1), m_rounded(false), m_moved(false), m_pressed(false)
{
    QLabel::setCursor(Qt::PointingHandCursor);
}

Label::~Label()
{
}

void Label::setOpacity(float opacity)
{
    m_opacity = opacity;

    repaint();
}

void Label::setRounded(bool rounded)
{
    m_rounded = rounded;
}

void Label::mousePressEvent(QMouseEvent* event)
{
    QLabel::mousePressEvent(event);

    if(!m_moved)
    {
        m_dragPoint = event->pos();
        m_pressed = true;
        m_time.start();
    }
}

void Label::mouseReleaseEvent(QMouseEvent* event)
{
    QLabel::mouseReleaseEvent(event);

    if(!m_moved && m_time.elapsed() < qApp->doubleClickInterval() && event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    m_moved = false;
    m_pressed = false;
}

void Label::mouseMoveEvent(QMouseEvent* event)
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

void Label::paintEvent(QPaintEvent* event)
{
    if(pixmap())
    {
        QImage image(pixmap()->toImage());
        QBrush brush(*pixmap());
        QPen pen(Qt::transparent);

        QPainter painter(this);
        painter.setBrush(brush);
        painter.setOpacity(m_opacity);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing);

        if(m_rounded)
        {
            QRect r = rect();
            r.setTopLeft(QPoint(r.topLeft().x() + contentsMargins().left(), r.topLeft().y() + contentsMargins().top()));
            r.setSize(pixmap()->size());

            painter.setBrushOrigin(r.topLeft());

            painter.drawRoundedRect(r, 10, 10);
        }
        else
        {
            painter.drawRect(rect());
        }
    }
    else
    {
        QPainter painter(this);
        painter.setOpacity(m_opacity);
        painter.setRenderHint(QPainter::TextAntialiasing);

        const QString elidedText = fontMetrics().elidedText(text(), Qt::ElideRight, contentsRect().width());
        painter.drawText(contentsRect(), alignment(), elidedText);

        QLabel::paintEvent(event);
    }
}
