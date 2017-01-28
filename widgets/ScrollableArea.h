#ifndef SCROLLABLEAREA_H
#define SCROLLABLEAREA_H

#include <QFileInfo>
#include <QScrollArea>

#include "Track.h"
#include "TrackLoader.h"

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
};

#endif // SCROLLABLEAREA_H
