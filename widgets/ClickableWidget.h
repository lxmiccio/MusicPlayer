#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QApplication>
#include <QTime>

#include "BackgroundWidget.h"

class ClickableWidget : public BackgroundWidget
{
        Q_OBJECT

    public:
        explicit ClickableWidget(QWidget* parent = 0);

    signals:
        void leftButtonClicked();
        void rightButtonClicked();

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);

    private:
        bool m_moved;
        bool m_pressed;
        QPoint m_dragPoint;
        QTime m_time;
};

#endif // CLICKABLEWIDGET_H
