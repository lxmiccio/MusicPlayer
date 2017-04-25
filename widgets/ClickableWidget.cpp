#include "ClickableWidget.h"

#include "ImageUtils.h"

ClickableWidget::ClickableWidget(QWidget* parent) : QWidget(parent), m_blurred(false)
{
    QWidget::setAutoFillBackground(false);
    setFocusPolicy(Qt::StrongFocus);
    m_backgroundColor = QColor(Qt::transparent);
}

void ClickableWidget::setBackgroundColor(const QColor& backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void ClickableWidget::setBackgroundImage(const QPixmap& pixmap, bool blurred, bool blackWhite)
{
    m_backgroundSlice = QPixmap();

    m_blurred = blurred;

    if(m_blurred)
        m_background = QPixmap::fromImage(ImageUtils::blur(pixmap.toImage(), pixmap.rect(), 10, false, blackWhite));
    else
        m_background = pixmap;

    repaint();
}

void ClickableWidget::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);

    if(!m_moved)
    {
        m_dragPoint = event->pos();
        m_pressed = true;
        m_time.start();
    }
}

void ClickableWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);

    if(!m_moved && m_time.elapsed() < qApp->doubleClickInterval())
    {
        if(event->button() == Qt::LeftButton)
        {
            emit leftButtonClicked();
        }

        if(event->button() == Qt::RightButton)
        {
            emit rightButtonClicked();
        }
    }

    m_moved = false;
    m_pressed = false;
}

void ClickableWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if(m_backgroundSlice.isNull() && !m_background.isNull())
    {
        m_backgroundSlice = m_background.scaledToWidth(contentsRect().width(), Qt::SmoothTransformation);
        m_backgroundSlice = m_backgroundSlice.copy(0, m_backgroundSlice.height() / 2 - contentsRect().height() / 2, m_backgroundSlice.width(), contentsRect().height());
    }

    if(!m_backgroundSlice.isNull())
    {
        painter.drawPixmap(contentsRect(), m_backgroundSlice.copy(contentsRect()));

        if(m_blurred)
        {
            painter.save();
            painter.setBrush(Qt::black);
            painter.setPen(Qt::transparent);
            painter.setOpacity(0.25);
            painter.drawRect(event->rect());
            painter.restore();
        }
    }
    else
    {
        painter.save();
        painter.setBrush(m_backgroundColor);
        painter.setPen(m_backgroundColor);
        painter.drawRect(event->rect());
        painter.restore();
    }

    QWidget::paintEvent(event);
}

void ClickableWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    m_backgroundSlice = QPixmap();
}
