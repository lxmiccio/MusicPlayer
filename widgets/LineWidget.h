#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QWidget>

class LineWidget : public QWidget
{
    public:
        LineWidget(Qt::Orientation orientation, QWidget* parent = 0);

        void setColor(QColor color);
        void setWidth(quint8 width);
        void setWidthF(qreal width);

        void setPen(QPen pen);

    protected:
        virtual void paintEvent(QPaintEvent* event);

    private:
        Qt::Orientation m_orientation;
        QPen m_pen;

        QHBoxLayout* m_layout;
};

#endif// LINEWIDGET_H
