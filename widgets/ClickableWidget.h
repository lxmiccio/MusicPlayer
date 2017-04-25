#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QApplication>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QTime>
#include <QWidget>

class ClickableWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit ClickableWidget(QWidget* parent = 0);

    public slots:
        virtual void setBackgroundColor(const QColor& backgroundColor);
        virtual void setBackgroundImage(const QPixmap& pixmap, bool blurred = false, bool blackWhite = false);

    signals:
        void leftButtonClicked();
        void rightButtonClicked();

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void paintEvent(QPaintEvent* event);
        virtual void resizeEvent(QResizeEvent* event);

    private:
        bool m_blurred;
        QColor m_backgroundColor;
        QPixmap m_background;
        QPixmap m_backgroundSlice;

        bool m_moved;
        bool m_pressed;
        QPoint m_dragPoint;
        QTime m_time;
};

#endif // CLICKABLEWIDGET_H
