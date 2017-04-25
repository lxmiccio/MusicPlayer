#include "ImageButton.h"

ImageButton::ImageButton(QWidget* parent) : QAbstractButton(parent)
{
}

void ImageButton::clear()
{
    setIcon(QIcon());
}

void ImageButton::setPixmap(const QString& path)
{
    QPixmap pixmap(path);

    m_sizeHint = pixmap.size();

    setPixmap(pixmap, QIcon::Off);
    updateGeometry();
}

void ImageButton::setPixmap(const QPixmap& pixmap)
{
    m_sizeHint = pixmap.size();

    setPixmap(pixmap, QIcon::Off);
    updateGeometry();
}

void ImageButton::setPixmap(const QString& path, const QIcon::State state, QIcon::Mode mode)
{
    setPixmap(QPixmap(path), state, mode);
}

void ImageButton::setPixmap(const QPixmap& pixmap, const QIcon::State state, QIcon::Mode mode)
{
    QIcon icon = this->icon();
    icon.addPixmap(pixmap, mode, state);

    setIcon(icon);
}

QSize ImageButton::sizeHint() const
{
    return m_sizeHint;
}

void ImageButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setClipRect(event->rect());

    QIcon::Mode mode = isDown() ? QIcon::Active : QIcon::Normal;
    QIcon::State state = isChecked() ? QIcon::On : QIcon::On;

    if(!isEnabled()) {
        painter.setOpacity(0.3);
    }

    icon().paint(&painter, rect(), Qt::AlignCenter, mode, state);
}
