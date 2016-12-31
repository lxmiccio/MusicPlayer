#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QTime>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = 0);
    virtual ~ClickableLabel();

    void setOpacity(float opacity);

signals:
    void clicked();
    void resized(const QPoint& delta);

protected:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);

private:
    float m_opacity;

    bool m_moved;
    QPoint m_dragPoint;

    bool m_pressed;
    QTime m_time;
};

#endif // CLICKABLELABEL_H
