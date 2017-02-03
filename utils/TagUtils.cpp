#include "TagUtils.h"

#include <QImage>
#include <QMap>
#include <QPixmap>

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

#include "MusicLibrary.h"

Track* TagUtils::readFlac(const QFileInfo& fileInfo)
{
    MusicLibrary* musicLibrary = MusicLibrary::instance();

    QPixmap cover = TagUtils::readFlacCover(fileInfo);
    // QString lyrics = TagUtils::readFlacLyrics(fileInfo);

    QVariantMap tags = TagUtils::readFlacTags(fileInfo).toMap();
    tags["cover"] = cover;
    // tags["lyrics"] = lyrics;

    //return musicLibrary->addTrack(tags);
}

QPixmap TagUtils::readFlacCover(const QFileInfo &fileInfo)
{
    TagLib::FLAC::File file(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));
    const TagLib::List<TagLib::FLAC::Picture*>& pictureList = file.pictureList();

    if(pictureList.size() > 0)
    {
        TagLib::FLAC::Picture* picture = pictureList[0];

        if(picture)
        {
            return QPixmap::fromImage(QImage::fromData(QByteArray(picture->data().data(), picture->width() * picture->height())));
        }
    }

    return QPixmap();
}

QString TagUtils::readFlacLyrics(const QFileInfo &fileInfo)
{
    //TODO
}

QVariant TagUtils::readFlacTags(const QFileInfo &fileInfo)
{
    TagLib::FLAC::File file(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));
    QVariantMap tags;

    if(file.isValid() && file.tag())
    {
        tags["track"] = file.tag()->track();
        tags["title"] = TagUtils::StringToQString(file.tag()->title());
        tags["path"] = fileInfo.canonicalFilePath();

        tags["album"] = TagUtils::StringToQString(file.tag()->album());
        tags["artist"] = TagUtils::StringToQString(file.tag()->artist());

        if(file.audioProperties())
        {
            tags["duration"] = file.audioProperties()->length();
        }
    }

    return tags;
}

Track* TagUtils::readMp3(const QFileInfo &fileInfo)
{
    MusicLibrary* musicLibrary = MusicLibrary::instance();

    QPixmap cover = TagUtils::readMp3Cover(fileInfo);
    QString lyrics = TagUtils::readMp3Lyrics(fileInfo);

    QVariantMap tags = TagUtils::readMp3Tags(fileInfo).toMap();
    tags["cover"] = cover;
    tags["lyrics"] = lyrics;

    return musicLibrary->addTrack(tags);
}

QPixmap TagUtils::readMp3Cover(const QFileInfo &fileInfo)
{
    QPixmap cover;
    TagLib::MPEG::File file(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));

    if(file.ID3v2Tag())
    {
        TagLib::ID3v2::FrameList frameList = file.ID3v2Tag()->frameListMap()["APIC"];
        if(!frameList.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame* pictureFrame;
            for(TagLib::ID3v2::FrameList::ConstIterator i_frame = frameList.begin(); i_frame != frameList.end() ; i_frame++)
            {
                pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(*i_frame);
                cover = QPixmap::fromImage(QImage::fromData(QByteArray(pictureFrame->picture().data(), pictureFrame->picture().size())));
            }
        }
    }

    return cover;
}

QString TagUtils::readMp3Lyrics(const QFileInfo &fileInfo)
{
    QString lyrics;
    TagLib::MPEG::File file(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));

    if(file.ID3v2Tag())
    {
        TagLib::ID3v2::FrameList frameList = file.ID3v2Tag()->frameListMap()["USLT"];
        if(!frameList.isEmpty())
        {
            TagLib::ID3v2::UnsynchronizedLyricsFrame* frame = dynamic_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame*>(frameList.front());
            if(frame)
            {
                lyrics = frame->text().toCString(true);
                lyrics.replace("\r", "\r\n");
            }
        }
    }

    return lyrics;
}

QVariant TagUtils::readMp3Tags(const QFileInfo &fileInfo)
{
    QVariantMap tags;
    TagLib::FileRef fileRef(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));

    if(!fileRef.isNull() && fileRef.tag())
    {
        tags["track"] = fileRef.tag()->track();
        tags["title"] = TagUtils::StringToQString(fileRef.tag()->title());
        tags["path"] = fileInfo.canonicalFilePath();

        tags["album"] = TagUtils::StringToQString(fileRef.tag()->album());
        tags["artist"] = TagUtils::StringToQString(fileRef.tag()->artist());

        if(fileRef.audioProperties())
        {
            tags["duration"] = fileRef.audioProperties()->length();
        }
    }

    return tags;
}

char* TagUtils::QStringToBuffer(const QString& string)
{
    return string.toUtf8().data();
}

QString TagUtils::StringToQString(const TagLib::String& string)
{
    return QString(string.toCString(true));
}

QString TagUtils::extensionToMimetype(const QString& extension)
{
    static QMap<QString, QString> extToMime;

    if(extToMime.isEmpty())
    {
        extToMime.insert("aac", "audio/mp4");
        extToMime.insert("aif", "audio/aiff");
        extToMime.insert("aiff", "audio/aiff");
        extToMime.insert("flac", "audio/flac");
        extToMime.insert("m4a", "audio/mp4");
        extToMime.insert("mp3", "audio/mpeg");
        extToMime.insert("mp4", "audio/mp4");
        extToMime.insert("mpc", "audio/x-musepack");
        extToMime.insert("ogg", "application/ogg");
        extToMime.insert("opus", "application/opus");
        extToMime.insert("wma", "audio/x-ms-wma");
        extToMime.insert("wv", "audio/x-wavpack");
    }

    return extToMime.value(extension.toLower(), "unknown");
}
