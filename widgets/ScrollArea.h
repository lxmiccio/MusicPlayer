#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QFileInfo>
#include <QScrollArea>

class ScrollArea : public QScrollArea
{
    Q_OBJECT

    public:
        explicit ScrollArea(QWidget* parent = 0);

    signals:
        void fileDropped(const QFileInfo& fileInfo);
        void resized(QResizeEvent* event);

    protected:
        virtual void dragEnterEvent(QDragEnterEvent* event);
        virtual void dropEvent(QDropEvent* event);
        virtual void resizeEvent(QResizeEvent* event);
};

#endif // SCROLLAREA_H
