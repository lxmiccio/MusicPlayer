#include "LineWidget.h"

LineWidget::LineWidget(Qt::Orientation orientation, QWidget* parent) : QWidget(parent)
{
    m_orientation = orientation;

    m_pen = QPen(Qt::white, 3);

    m_layout = new QHBoxLayout();
    setLayout(m_layout);
}

void LineWidget::setPen(QPen pen)
{
    m_pen = pen;
}

void LineWidget::paintEvent(QPaintEvent* event)
{
    QPointF point1 = QPointF(event->rect().topLeft().x(), event->rect().topLeft().y());
    QPointF point2;

    if(m_orientation == Qt::Horizontal)
    {
        point2 = QPointF(event->rect().topRight().x(), event->rect().topRight().y());
    }
    else
    {
        point2 = QPointF(event->rect().bottomLeft().x(), event->rect().bottomLeft().y());
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(m_pen);

    painter.drawLine(point1, point2);
}
