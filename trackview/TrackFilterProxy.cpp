#include "TrackFilterProxy.h"

TrackFilterProxy::TrackFilterProxy(quint8 mode, QObject* parent) : QSortFilterProxyModel(parent)
{
    m_mode = mode;
}

bool TrackFilterProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
#if 0
    quint8 columns = sourceModel()->columnCount();

    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if (leftData.type() == QVariant::DateTime) {
        return leftData.toDateTime() < rightData.toDateTime();
    } else {
        QRegExp *emailPattern = new QRegExp("([\\w\\.]*@[\\w\\.]*)");

        QString leftString = leftData.toString();
        if(left.column() == 1 && emailPattern->indexIn(leftString) != -1)
            leftString = emailPattern->cap(1);

        QString rightString = rightData.toString();
        if(right.column() == 1 && emailPattern->indexIn(rightString) != -1)
            rightString = emailPattern->cap(1);

        return QString::localeAwareCompare(leftString, rightString) < 0;
    }
#endif
}
