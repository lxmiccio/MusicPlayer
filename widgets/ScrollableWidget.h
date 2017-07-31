#ifndef SCROLLABLEWIDGET_H
#define SCROLLABLEWIDGET_H

#include <QCommonStyle>
#include <QDragEnterEvent>
#include <QDirIterator>
#include <QFileInfo>
#include <QMimeData>
#include <QScrollArea>
#include <QScrollBar>

class ScrollableWidget : public QScrollArea
{
        Q_OBJECT

    public:
        explicit ScrollableWidget(QWidget* parent = 0);

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

#endif// SCROLLABLEWIDGET_H
