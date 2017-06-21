#ifndef ARTISTWIDGET_H
#define ARTISTWIDGET_H

#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>

#include "Artist.h"
#include "ClickableLabel.h"
#include "ClickableWidget.h"
#include "ElidedLabel.h"

class ArtistWidget : public ClickableWidget
{
        Q_OBJECT

    public:
        explicit ArtistWidget(Artist* artist, QWidget* parent = 0);
        ~ArtistWidget();

        Artist* artist() const;

        void focusIn();
        void focusOut();

        static const quint16 WIDGET_HEIGHT = 60;
        static const quint16 WIDGET_WIDTH = 300;
        static const quint16 IMAGE_HEIGHT = 60;
        static const quint16 IMAGE_WIDTH = 60;

    signals:
        void removeArtistWidgetClicked(ArtistWidget* widget);
        void widgetClicked(ArtistWidget* widget);

    protected:
        virtual void paintEvent(QPaintEvent* event);

    private slots:
        void onContextMenuRequested(QPoint position);
        void onLeftButtonClicked();

    private:
        Artist* m_artist;
        bool m_focussed;

        QLabel* m_cover;
        ElidedLabel* m_artistName;

        QHBoxLayout* m_layout;
};

#endif// ARTISTWIDGET_H
