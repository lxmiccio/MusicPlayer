#ifndef ALBUMSTRACKSLISTVIEW_H
#define ALBUMSTRACKSLISTVIEW_H

#include <QListView>

#include "AlbumsTracksListDelegate.h"
#include "AlbumsTracksListModel.h"

class AlbumsTracksListDelegate;
\
class AlbumsTracksListView : public QListView
{
        Q_OBJECT

    public:
        AlbumsTracksListView(bool sort = true, QWidget* parent = 0);
        ~AlbumsTracksListView();

        AlbumsTracksListModel* albumsTracksListModel() const;

        int rowCount() const;
        int columnCount() const;
        void propendItem(Album* album);
        void insertItemAt(Album* album, int row);
        void removeFirstItem();
        void removeLastItem();
        void removeItemAt(int row);
        void clear();

        QSize maxSize();

    public slots:
        void appendItem(Album* album);
        void removeItem(Album* album);

    private:
        AlbumsTracksListModel* m_albumsTracksListModel;
        AlbumsTracksListDelegate* m_albumsTracksListDelegate;
};

#endif // ALBUMSTRACKSLISTVIEW_
