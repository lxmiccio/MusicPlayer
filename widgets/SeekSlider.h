#ifndef SEEKSLIDER_H
#define SEEKSLIDER_H

#include <QSlider>
#include <QTimeLine>

class SeekSlider : public QSlider
{
    public:
        SeekSlider(Qt::Orientation orientation, QWidget* parent = 0);

        void setAcceptWheelEvents(bool accept);
        void setLockScubbing(bool lock);
        void setTimeLine(QTimeLine* timeline);

        static const quint8 HORIZONTAL_SLIDER_WIDTH = 10;

    public slots:
        void setValue(int value);

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void wheelEvent(QWheelEvent* event);

    private:
        bool m_acceptWheelEvents;
        bool m_lockScrubbing;
        bool m_scrubbing;
        QTimeLine* m_timeLine;
};

#endif // SEEKSLIDER_H
