#include "SeekSlider.h"

#include <QMouseEvent>

SeekSlider::SeekSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(parent), m_acceptWheelEvents(false), m_isScrubbing(false), m_timeLine(0)
{
  setOrientation(orientation);

  setStyleSheet(QString("QSlider::groove:horizontal {"
                        "background: rgba(200, 200, 200, 40);"
                        "border: 1px solid rgba(0, 0, 0, 25);"
                        "margin-bottom: 0px;"
                        "margin-left: 0px;"
                        "margin-right: 0px;"
                        "margin-top: 0px;"
                        "}"
                        "QSlider::sub-page:horizontal {"
                        "background: %1;"
                        "margin-bottom: 1px;"
                        "margin-left: 1px;"
                        "margin-right: 0px;"
                        "margin-top: 1px;"
                        "}")
                .arg(QColor("#ffffff").name()));
}

void SeekSlider::setAcceptWheelEvents(bool accept)
{
  this->m_acceptWheelEvents = accept;
}

void SeekSlider::setTimeLine(QTimeLine *timeline)
{
  this->m_timeLine = timeline;
}

void SeekSlider::setValue(int value)
{
  if(m_timeLine and this->sender() == m_timeLine) {
    this->blockSignals(true);
    QSlider::setValue(value);
    this->blockSignals(false);
  } else {
    QSlider::setValue(value);
  }
}

void SeekSlider::mouseMoveEvent(QMouseEvent* event)
{
  if(this->m_isScrubbing) {
    if(event->pos().x() > width()) {
      this->m_isScrubbing = false;
    } else {
      QSlider::mouseMoveEvent( event );
    }
  }
}

void SeekSlider::mousePressEvent(QMouseEvent* event)
{
  if(event->button() == Qt::LeftButton) {
    this->m_isScrubbing = true;

    QMouseEvent eventSwap = QMouseEvent(QEvent::MouseButtonRelease, event->pos(), event->globalPos(), Qt::MidButton, Qt::MidButton, event->modifiers());
    QSlider::mousePressEvent(&eventSwap);
  } else {
    QSlider::mousePressEvent( event );
  }
}

void SeekSlider::wheelEvent(QWheelEvent* event)
{
  if (this->m_acceptWheelEvents) {
    QAbstractSlider::wheelEvent(event);
  } else {
    event->ignore();
  }
}
