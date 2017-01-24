#ifndef TAGUTILS_H
#define TAGUTILS_H

#include <QString>
#include <QFileInfo>
#include <QVariant>

#include "taglib/tag.h"

#include "Track.h"

class TagUtils
{
    public:
        static Track* readFlac(const QFileInfo &fileInfo);
        static QPixmap readFlacCover(const QFileInfo& fileInfo);
        static QString readFlacLyrics(const QFileInfo& fileInfo);
        static QVariant readFlacTags(const QFileInfo& fileInfo);

        static Track* readMp3(const QFileInfo &fileInfo);
        static QPixmap readMp3Cover(const QFileInfo& fileInfo);
        static QString readMp3Lyrics(const QFileInfo& fileInfo);
        static QVariant readMp3Tags(const QFileInfo& fileInfo);

        static char* QStringToBuffer(const QString& string);
        static QString StringToQString(const TagLib::String& string);

        static QString extensionToMimetype(const QString &extension);
};

#endif // TAGUTILS_H
