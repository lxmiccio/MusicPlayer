#ifndef LINE_H
#define LINE_H

#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPen>
#include <QWidget>

class Line : public QWidget
{
    public:
        Line(Qt::Orientation orientation, QWidget* parent = 0);
        void setPen(QPen pen);

    protected:
        virtual void paintEvent(QPaintEvent* event);

    private:
        Qt::Orientation m_orientation;
        QPen m_pen;
        QHBoxLayout* m_layout;
};

#endif // LINE_H
