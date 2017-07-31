#ifndef ARISTSLISTVIEW_H
#define ARISTSLISTVIEW_H

#include <QListView>

#include "ArtistsListDelegate.h"
#include "ArtistsListModel.h"

class ArtistsListDelegate;

class ArtistsListView : public QListView
{
        Q_OBJECT

    public:
        explicit ArtistsListView(bool sort = true, QWidget* parent = 0);
        ~ArtistsListView();

        ArtistsListModel* artistsListModel() const;

        int rowCount() const;
        int columnCount() const;
        void propendItem(Artist* artist);
        void insertItemAt(Artist* artist, int row);
        void removeFirstItem();
        void removeLastItem();
        void removeItemAt(int row);
        void clear();

        QSize maxSize();

    public slots:
        void appendItem(Artist* artist);
        void removeItem(Artist* artist);

    signals:
        void artistClicked(Artist* artist);
        void artistEntered(Artist* artist);
        void artistPressed(Artist* artist);
        void artistSelected(Artist* artist);
        void artistDoubleClicked(Artist* artist);

    private slots:
        void onContextMenuRequested(QPoint position);
        void onItemClicked(const QModelIndex& index);
        void onItemEntered(const QModelIndex& index);
        void onItemPressed(const QModelIndex& index);
        void onItemDoubleClicked(const QModelIndex& index);
        void onCurrentRowChanged(QModelIndex current, QModelIndex previous);

    private:
        ArtistsListModel* m_artistsListModel;
        ArtistsListDelegate* m_artistsListDelegate;
};

#endif // ARISTSLISTVIEW_H
