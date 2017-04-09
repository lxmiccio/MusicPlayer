#include "TrackFilterProxy.h"

TrackFilterProxy::TrackFilterProxy(QObject* parent) : QSortFilterProxyModel(parent)
{
}

bool TrackFilterProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    static QVector<quint8> indexesToCompare;

    if(indexesToCompare.isEmpty())
    {
        indexesToCompare.append(TrackView::ARTIST_INDEX);
        indexesToCompare.append(TrackView::ALBUM_INDEX);
        indexesToCompare.append(TrackView::TRACK_INDEX);
        indexesToCompare.append(TrackView::TITLE_INDEX);
        /*
        indexesToCompare.append(TrackView::ARTIST_INDEX);
        indexesToCompare.append(TrackView::ALBUM_INDEX);
        indexesToCompare.append(TrackView::TRACK_INDEX);
        indexesToCompare.append(TrackView::TITLE_INDEX);
        */
    }

    int leftRow = left.row();
    int rightRow = right.row();

    for(quint8 i = 0; i < indexesToCompare.size(); ++i)
    {
        QModelIndex leftIndex = sourceModel()->index(leftRow, indexesToCompare.at(i), QModelIndex());
        QModelIndex rightIndex = sourceModel()->index(rightRow, indexesToCompare.at(i), QModelIndex());

        if(indexesToCompare.at(i) == 0)
        {
            int leftData = sourceModel()->data(leftIndex).toInt();
            int rightData = sourceModel()->data(rightIndex).toInt();

            if(leftData != rightData)
            {
                return leftData < rightData;
            }
        }
        else
        {
            QString leftData = sourceModel()->data(leftIndex).toString();
            QString rightData = sourceModel()->data(rightIndex).toString();

            if(QString::compare(leftData, rightData) != 0)
            {
                return QString::compare(leftData, rightData) < 0;
            }
        }
    }

    return false;
}
