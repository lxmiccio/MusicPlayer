#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QFileInfo>
#include <QScrollArea>

#include "Track.h"

class ScrollArea : public QScrollArea
{
        Q_OBJECT

    public:
        explicit ScrollArea(QWidget* parent = 0);

    private slots:
        void onTrackLoaded(const Track& track);

    signals:
        void flacDropped(const QFileInfo& fileInfo);
        void mp3Dropped(const QFileInfo& fileInfo);
        void resized(QResizeEvent* event);
        void trackLoaded(const Track& track);

    protected:
        virtual void dragEnterEvent(QDragEnterEvent* event);
        virtual void dropEvent(QDropEvent* event);
        virtual void resizeEvent(QResizeEvent* event);
};

#endif // SCROLLAREA_H
