#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
    public:
        static const QString secondsToMinutes(quint16 seconds);
        static quint16 stringToSeconds(QString minutes);
};

#endif // UTILS_H
