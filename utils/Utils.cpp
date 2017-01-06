#include "Utils.h"

#include <QtMath>
#include <QStringList>

const QString Utils::secondsToMinutes(quint16 seconds)
{
    return QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'));
}

quint16 Utils::stringToSeconds(QString minutes)
{
    quint16 seconds = 0;

    QStringList time = minutes.split(":");
    QStringListIterator iterator(time);
    iterator.toBack();

    for(quint8 i = 0; iterator.hasNext(); i++)
    {
        seconds += iterator.next().toUInt() * qPow(60, i);
    }

    return seconds;
}
