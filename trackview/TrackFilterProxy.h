#ifndef TRACKFILTERPROXY_H
#define TRACKFILTERPROXY_H

#include <QSortFilterProxyModel>

class TrackFilterProxy : public QSortFilterProxyModel
{
        Q_OBJECT

    public:
        TrackFilterProxy(quint8 mode, QObject* parent = 0);

    protected:
        bool lessThan(const QModelIndex & left, const QModelIndex & right) const;

    private:
        quint8 m_mode;
};

#endif // TRACKFILTERPROXY_H
