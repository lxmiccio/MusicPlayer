#include "LineWidget.h"

LineWidget::LineWidget(Qt::Orientation orientation, QWidget* parent) : QWidget(parent)
{
    m_orientation = orientation;

    m_pen = QPen(Qt::white, 3);

    m_layout = new QHBoxLayout();
    setLayout(m_layout);
}

void LineWidget::setColor(QColor color)
{
    m_pen.setColor(color);
}

void LineWidget::setWidth(quint8 width)
{
    m_pen.setWidth(width);
}

void LineWidget::setWidthF(qreal width)
{
    m_pen.setWidthF(width);
}

void LineWidget::setPen(QPen pen)
{
    m_pen = pen;
}

void LineWidget::paintEvent(QPaintEvent* event)
{
    QPointF point1 = QPointF(event->rect().topLeft().x() + contentsMargins().left(), event->rect().topLeft().y() + contentsMargins().top());
    QPointF point2;

    if(m_orientation == Qt::Horizontal)
    {
        point2 = QPointF(event->rect().topRight().x() - contentsMargins().right(), event->rect().topRight().y() + contentsMargins().top());
    }
    else
    {
        point2 = QPointF(event->rect().bottomLeft().x() + contentsMargins().left(), event->rect().bottomLeft().y() - contentsMargins().bottom());
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(m_pen);

    painter.drawLine(point1, point2);
}
