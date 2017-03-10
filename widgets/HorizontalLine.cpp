#include "HorizontalLine.h"

#include <QPainter>

HorizontalLine::HorizontalLine(QWidget* parent) : QWidget(parent)
{
    m_layout = new QHBoxLayout();
    setLayout(m_layout);
}

void HorizontalLine::paintEvent(QPaintEvent* event)
{
    QPointF p1 = QPointF(event->rect().topLeft().x(), event->rect().topLeft().y());
    QPointF p2 = QPointF(event->rect().topRight().x(), event->rect().topRight().y());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 3));

    painter.drawLine(p1, p2);
}
