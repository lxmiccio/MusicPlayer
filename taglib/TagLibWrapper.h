#ifndef TAGLIBWRAPPER_H
#define TAGLIBWRAPPER_H

#include <QFileInfo>
#include <QImage>
#include <QMap>
#include <QPixmap>
#include <QString>
#include <QVariantMap>

#include <attachedPictureFrame.h>
#include <fileref.h>
#include <flacfile.h>
#include <id3v2frame.h>
#include <id3v2header.h>
#include <id3v2tag.h>
#include <mp4file.h>
#include <mpegfile.h>
#include <tag.h>
#include <unsynchronizedlyricsframe.h>

#include "Utils.h"

struct Mp3Tags
{
        QString album;
        QString artist;
        QString title;
        quint16 track;
        quint32 year;

        quint32 bitrate;
        quint32 channels;
        quint32 duration;
        quint32 samplerate;

        QPixmap cover;
        QString lyrics;

        QString path;
};

class TagLibWrapper
{
    public:
        static QPixmap readFlacCover(const QFileInfo& fileInfo);
        static QString readFlacLyrics(const QFileInfo& fileInfo);
        static void readFlacTags(const QString& filename, Mp3Tags* tags);

        static QPixmap readMp3Cover(const QFileInfo& fileInfo);
        static void readMp3Lyrics(const QString& filename, Mp3Tags* tags);
        static void readMp3Tags(const QString& filename, Mp3Tags* tags);
        static void setMp3Cover(const QString& filename, const QPixmap& cover);
        static void setMp3Tags(const QString& filename, const Mp3Tags tags);

        static QString extensionToMimetype(const QString &extension);
};

#endif // TAGLIBWRAPPER_H
