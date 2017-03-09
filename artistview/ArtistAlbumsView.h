#ifndef ARTISTALBUMSVIEW_H
#define ARTISTALBUMSVIEW_H

#include <QMutex>
#include <QMutexLocker>
#include <QVBoxLayout>
#include <QWidget>

#include "Artist.h"
#include "ArtistAlbumWidget.h"

class ArtistAlbumsView : public QWidget
{
        Q_OBJECT

    public:
        ArtistAlbumsView(QWidget* parent = 0);


        void clearLayout(QLayout* layout)
        {
            QLayoutItem* i_item;

            while((i_item = layout->takeAt(0)) != NULL)
            {
                if(i_item->layout())
                {
                    clearLayout(i_item->layout());
                    delete i_item->layout();
                }
                if(i_item->widget())
                {
                    delete i_item->widget();
                }

                delete i_item;
            }
        }

    public slots:
        void onArtistChanged(const Artist* artist);

    private:
        QMutex m_mutex;
        QVector<ArtistAlbumWidget*> m_widgets;
        QVBoxLayout* m_layout;
};

#endif // ARTISTALBUMSVIEW_H
