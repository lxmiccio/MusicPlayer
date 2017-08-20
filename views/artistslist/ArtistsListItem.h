#ifndef ARTISTSLISTITEM_H
#define ARTISTSLISTITEM_H

#include <QHBoxLayout>
#include <QWidget>

#include "Artist.h"
#include "Label.h"

class ArtistsListItem : public QWidget
{
        Q_OBJECT

    public:
        explicit ArtistsListItem(bool sort = true);
        explicit ArtistsListItem(Artist* artist, ArtistsListItem* parent);
        ~ArtistsListItem();

        virtual QSize sizeHint();

        QVariant data(int column) const;

        ArtistsListItem* parent() const;
        int row() const;

        ArtistsListItem* child(int row) const;
        int columnCount() const;
        int rowCount() const;

        int indexOf(Artist* artist);
        void prependChild(ArtistsListItem* item);
        void appendChild(ArtistsListItem* item);
        void insertChildAt(ArtistsListItem* item, int row);
        void removeFirstChild();
        void removeChild(ArtistsListItem* item);
        void removeChildAt(int row);
        void removeLastChild();
        void clear();

        Artist* artist() const;

    private slots:
        void onArtistUpdated(Artist* artist, quint8 fields);

    signals:
        void itemUpdated();

    private:
        void sort();
        bool m_sort;

        Artist* m_artist;

        Label* m_cover;
        QLabel* m_artistName;

        QHBoxLayout* m_layout;

        ArtistsListItem* m_parent;
        QList<ArtistsListItem*> m_childs;
};

#endif // ARTISTSLISTITEM_H
