#ifndef UTILS_H
#define UTILS_H

#include <QtMath>
#include <QString>
#include <QStringList>
#include <QStringListIterator>

class Utils
{
    public:
        static quint32 randomInteger(quint32 min, quint32 max);
        static QString randomString(quint32 length = 16);
        static const QString secondsToMinutes(quint32 seconds);
        static quint32 stringToSeconds(QString minutes);
};

#endif // UTILS_H
