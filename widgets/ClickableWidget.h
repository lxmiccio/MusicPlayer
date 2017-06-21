#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QApplication>
#include <QLayout>
#include <QMouseEvent>
#include <QTime>
#include <QWidget>

class ClickableWidget : public QWidget
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

        void clearLayout(QLayout* layout);
        void deleteLayout(QLayout* layout);

    private:
        bool m_moved;
        bool m_pressed;
        QPoint m_dragPoint;
        QTime m_time;
};

#endif// CLICKABLEWIDGET_H
