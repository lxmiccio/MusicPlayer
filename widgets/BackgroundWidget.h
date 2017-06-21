#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include <QLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QWidget>

class BackgroundWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit BackgroundWidget(QWidget* parent = 0);

    public slots:
        virtual void setBackgroundColor(const QColor& backgroundColor);
        virtual void setBackgroundImage(const QPixmap& pixmap, bool blurred = false, bool blackWhite = false);

    protected:
        virtual void paintEvent(QPaintEvent* event);
        virtual void resizeEvent(QResizeEvent* event);

        void clearLayout(QLayout* layout);
        void deleteLayout(QLayout* layout);

    private:
        bool m_blurred;
        QColor m_backgroundColor;
        QPixmap m_background;
        QPixmap m_backgroundSlice;
};

#endif// BACKGROUNDWIDGET_H
