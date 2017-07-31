#include "ClickableWidget.h"

#include "ImageUtils.h"

ClickableWidget::ClickableWidget(QWidget* parent) : QWidget(parent)
{
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

void ClickableWidget::clearLayout(QLayout* layout)
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

void ClickableWidget::deleteLayout(QLayout* layout)
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
