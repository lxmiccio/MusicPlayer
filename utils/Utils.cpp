#include "Utils.h"

quint32 Utils::randomInteger(quint32 min, quint32 max)
{
    if(min < max)
    {
        qSwap(min, max);
    }

    return (qrand() % ((max + 1) - min)) + min;
}

QString Utils::randomString(quint32 length)
{
    static const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    QString randomString;
    for(quint8 i = 0; i < length; ++i)
    {
        QChar nextChar = possibleCharacters.at(Utils::randomInteger(0, possibleCharacters.length() - 1));
        randomString.append(nextChar);
    }

    return randomString;
}

const QString Utils::secondsToMinutes(quint32 seconds)
{
    return QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'));
}

quint32 Utils::stringToSeconds(QString minutes)
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
