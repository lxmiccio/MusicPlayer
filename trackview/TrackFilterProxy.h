#ifndef TRACKFILTERPROXY_H
#define TRACKFILTERPROXY_H

#include <QSortFilterProxyModel>

#include "TrackView.h"

class TrackView;

class TrackFilterProxy : public QSortFilterProxyModel
{
        Q_OBJECT

    public:
        TrackFilterProxy(QObject* parent = 0);

    protected:
        bool lessThan(const QModelIndex& left, const QModelIndex& right) const;
};

#endif // TRACKFILTERPROXY_H
