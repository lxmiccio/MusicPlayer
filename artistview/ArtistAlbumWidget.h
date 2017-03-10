#ifndef ARTISTALBUMWIDGET_H
#define ARTISTALBUMWIDGET_H

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "ElidedLabel.h"

#include "TrackItem.h"
#include "TrackList.h"
#include "TrackModel.h"
#include "TrackDelegate.h"

class ArtistAlbumWidget : public QWidget
{
        Q_OBJECT

    public:
        ArtistAlbumWidget(QWidget* parent = 0);
        void setAlbum(Album* album);

        static const quint16 IMAGE_HEIGHT = 100;
        static const quint16 IMAGE_WIDTH = 100;

    protected:
        virtual QSize sizeHint()
        {
            QSize hint = QWidget::sizeHint();

            if(m_layout && m_trackList)
            {
                hint.setHeight(ArtistAlbumWidget::IMAGE_HEIGHT + 40 + m_trackList->fittingSize().height());
            }

            return hint;
        }


    signals:
        void trackClicked(Track* track);

    private slots:
        void onDoubleClicked(const QModelIndex& index);

    private:
        void clear();

        Album* m_album;
        QLabel* m_cover;
        ElidedLabel* m_albumTitle;

        QVector<TrackItem*> m_items;
        TrackList* m_trackList;
        TrackModel* m_model;
        TrackDelegate* m_delegate;

        QVBoxLayout* m_layout;
        QHBoxLayout* m_upperLayout;
        QHBoxLayout* m_lowerLayout;

        QSpacerItem* m_upperLayoutLeftSpacer;
        QSpacerItem* m_upperLayoutRightSpacer;
        QSpacerItem* m_middleSpacer;
        QSpacerItem* m_lowerLayoutLeftSpacer;
        QSpacerItem* m_lowerSpacer;
};

#endif // ARTISTALBUMWIDGET_H
