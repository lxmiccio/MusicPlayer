#ifndef SLIDER_H
#define SLIDER_H

#include <QMouseEvent>
#include <QSlider>

class Slider : public QSlider
{
        Q_OBJECT

    public:
        Slider(Qt::Orientation orientation, QWidget* parent = 0);

        void setAcceptWheelEvents(bool accept);
        void setLockScubbing(bool lock);

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void wheelEvent(QWheelEvent* event);

    private:
        bool m_acceptWheelEvents;
        bool m_lockScrubbing;
        bool m_scrubbing;
};

#endif // SLIDER_H
