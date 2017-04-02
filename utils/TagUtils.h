#ifndef TAGUTILS_H
#define TAGUTILS_H

#include <QFileInfo>
#include <QImage>
#include <QMap>
#include <QPixmap>
#include <QString>
#include <QVariantMap>

#include <taglib/attachedPictureFrame.h>
#include <taglib/fileref.h>
#include <taglib/flacfile.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/id3v2tag.h>
#include <taglib/mp4file.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>
#include <taglib/unsynchronizedlyricsframe.h>

#include "Utils.h"

class TagUtils
{
    public:
        static QPixmap readFlacCover(const QFileInfo& fileInfo);
        static QString readFlacLyrics(const QFileInfo& fileInfo);
        static void readFlacTags(const QFileInfo& fileInfo, QVariantMap* map);

        static QPixmap readMp3Cover(const QFileInfo& fileInfo);
        static void readMp3Lyrics(const QFileInfo& fileInfo, QVariantMap* map);
        static void readMp3Tags(const QFileInfo& fileInfo, QVariantMap* map);

        static QString extensionToMimetype(const QString &extension);
};

#endif // TAGUTILS_H
