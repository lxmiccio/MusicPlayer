#ifndef ARTISTWIDGET_H
#define ARTISTWIDGET_H

#include <QHBoxLayout>
#include <QPoint>

#include "Artist.h"
#include "ClickableLabel.h"
#include "ElidedLabel.h"

class ArtistWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit ArtistWidget(const Artist* artist, QWidget* parent = 0);
        ~ArtistWidget();

        const Artist* artist() const;

        static const quint16 WIDGET_HEIGHT = 60;
        static const quint16 WIDGET_WIDTH = 300;
        static const quint16 IMAGE_HEIGHT = 60;
        static const quint16 IMAGE_WIDTH = 60;

    signals:
        void coverClicked(const Artist* artist);
        void removeArtistWidgetClicked(ArtistWidget* widget);

    private slots:
        void onCoverClicked();
        void onContextMenuRequested(QPoint pos);

    private:
        const Artist* c_artist;

        ClickableLabel* m_cover;
        ElidedLabel* m_artistName;
        QHBoxLayout* m_layout;
};

#endif // ARTISTWIDGET_H
