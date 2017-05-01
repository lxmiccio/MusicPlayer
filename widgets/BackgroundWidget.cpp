#include "BackgroundWidget.h"

#include "ImageUtils.h"

BackgroundWidget::BackgroundWidget(QWidget* parent) : QWidget(parent), m_blurred(false)
{
    QWidget::setAutoFillBackground(false);

    setBackgroundColor(Qt::transparent);
}

void BackgroundWidget::setBackgroundColor(const QColor& backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void BackgroundWidget::setBackgroundImage(const QPixmap& pixmap, bool blurred, bool blackWhite)
{
    m_backgroundSlice = QPixmap();

    m_blurred = blurred;

    if(m_blurred)
    {
        m_background = QPixmap::fromImage(ImageUtils::blur(pixmap.toImage(), pixmap.rect(), 10, false, blackWhite));
    }
    else
    {
        m_background = pixmap;
    }

    repaint();
}

void BackgroundWidget::paintEvent(QPaintEvent* event)
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

void BackgroundWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    m_backgroundSlice = QPixmap();
}

void BackgroundWidget::clearLayout(QLayout* layout)
{
    QLayoutItem* i_item;

    while((i_item = layout->takeAt(0)) != NULL)
    {
        if(i_item->layout())
        {
            deleteLayout(i_item->layout());
            delete i_item->layout();
        }
    }
}

void BackgroundWidget::deleteLayout(QLayout* layout)
{
    QLayoutItem* i_item;

    while((i_item = layout->takeAt(0)) != NULL)
    {
        if(i_item->layout())
        {
            deleteLayout(i_item->layout());
            delete i_item->layout();
        }

        if(i_item->widget())
        {
            delete i_item->widget();
        }

        delete i_item;
    }
}
