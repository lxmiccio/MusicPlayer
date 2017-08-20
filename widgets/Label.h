#ifndef LABEL_H
#define LABEL_H

#include <QApplication>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>

class Label : public QLabel
{
        Q_OBJECT

    public:
        explicit Label(QWidget* parent = 0);
        virtual ~Label();

        void setOpacity(float opacity);
        void setRounded(bool rounded);

    signals:
        void clicked();
        void resized(const QPoint& delta);

    protected:
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void paintEvent(QPaintEvent* event);

    private:
        float m_opacity;

        bool m_rounded;

        bool m_moved;
        QPoint m_dragPoint;

        bool m_pressed;
        QTime m_time;
};

#endif// LABEL_H
