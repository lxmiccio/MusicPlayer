#ifndef SCROLLABLEAREA_H
#define SCROLLABLEAREA_H

#include <QCommonStyle>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QScrollArea>
#include <QScrollBar>

class ScrollableArea : public QScrollArea
{
        Q_OBJECT

    public:
        explicit ScrollableArea(QWidget* parent = 0);

    signals:
        void filesDropped(const QVector<QFileInfo>& filesInfo);
        void resized(QResizeEvent* event);

    protected:
        virtual void dragEnterEvent(QDragEnterEvent* event);
        virtual void dropEvent(QDropEvent* event);
        virtual void resizeEvent(QResizeEvent* event);

        void clearLayout(QLayout* layout);
        void deleteLayout(QLayout* layout);
};

#endif // SCROLLABLEAREA_H
