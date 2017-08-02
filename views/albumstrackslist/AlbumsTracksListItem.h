#ifndef ALBUMSTRACKSLISTITEM_H
#define ALBUMSTRACKSLISTITEM_H

#include "AlbumInfoView.h"

class AlbumsTracksListItem : public AlbumInfoView
{
    public:
        explicit AlbumsTracksListItem(bool sort = true);
        explicit AlbumsTracksListItem(Album* album, AlbumsTracksListItem* parent);
        ~AlbumsTracksListItem();

        QVariant data(int column) const;

        AlbumsTracksListItem* parent() const;
        int row() const;

        AlbumsTracksListItem* child(int row) const;
        int columnCount() const;
        int rowCount() const;

        int indexOf(Album* album);
        void prependChild(AlbumsTracksListItem* item);
        void appendChild(AlbumsTracksListItem* item);
        void insertChildAt(AlbumsTracksListItem* item, int row);
        void removeFirstChild();
        void removeChild(AlbumsTracksListItem* item);
        void removeChildAt(int row);
        void removeLastChild();
        void clear();

        Album* album() const;

    private slots:
        void onAlbumUpdated(Album* album, quint8 fields);

    private:
        void sort();
        bool m_sort;

        Album* m_album;

        AlbumsTracksListItem* m_parent;
        QList<AlbumsTracksListItem*> m_childs;
};

#endif // ALBUMSTRACKSLISTITEM_H
