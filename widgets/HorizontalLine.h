#ifndef HORIZONTALLINE_H
#define HORIZONTALLINE_H

#include <QHBoxLayout>
#include <QPaintEvent>
#include <QWidget>

class HorizontalLine : public QWidget
{
    public:
        HorizontalLine(QWidget* parent = 0);

    protected:
        virtual void paintEvent(QPaintEvent* event);

    private:
        QHBoxLayout* m_layout;
};

#endif // HORIZONTALLINE_H
