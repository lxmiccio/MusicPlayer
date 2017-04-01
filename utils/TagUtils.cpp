#include "TagUtils.h"

QPixmap TagUtils::readFlacCover(const QFileInfo &fileInfo)
{
    TagLib::FLAC::File file(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));
    const TagLib::List<TagLib::FLAC::Picture*>& pictureList = file.pictureList();

    if(pictureList.size() > 0)
    {
        TagLib::FLAC::Picture* picture = pictureList[0];

        if(picture)
        {
            return QPixmap::fromImage(QImage::fromData(QByteArray(picture->data().data(), static_cast<int>(picture->data().size()))));
        }
    }

    return QPixmap();
}

QString TagUtils::readFlacLyrics(const QFileInfo &fileInfo)
{
    Q_UNUSED(fileInfo);

    //TODO --> read .lrc file if exists
    return QString();
}

void TagUtils::readFlacTags(const QFileInfo &fileInfo, QVariantMap* map)
{
    if(map)
    {
        TagLib::FLAC::File file(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));

        if(file.isValid() && file.tag())
        {
            map->insert("track", file.tag()->track());
            map->insert("title", TagUtils::StringToQString(file.tag()->title()));
            map->insert("album", TagUtils::StringToQString(file.tag()->album()));
            map->insert("artist", TagUtils::StringToQString(file.tag()->artist()));
            map->insert("path", fileInfo.canonicalFilePath());

            if(file.audioProperties())
            {
                map->insert("duration", file.audioProperties()->length());
            }
        }
    }
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
                cover = QPixmap::fromImage(QImage::fromData(QByteArray(pictureFrame->picture().data(), static_cast<int>(pictureFrame->picture().size()))));
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

void TagUtils::readMp3Tags(const QFileInfo &fileInfo, QVariantMap* map)
{
    if(map)
    {
#ifndef DEBUG
        TagLib::FileRef fileRef(TagUtils::QStringToBuffer(fileInfo.canonicalFilePath()));

        if(!fileRef.isNull() && fileRef.tag())
        {
            map->insert("track", fileRef.tag()->track());
            map->insert("title", TagUtils::StringToQString(fileRef.tag()->title()));
            map->insert("album", TagUtils::StringToQString(fileRef.tag()->album()));
            map->insert("artist", TagUtils::StringToQString(fileRef.tag()->artist()));
            map->insert("path", fileInfo.canonicalFilePath());

            if(fileRef.audioProperties())
            {
                map->insert("duration", fileRef.audioProperties()->lengthInSeconds());
            }
        }
#else
        map->insert("track", 1);
        map->insert("title", Utils::randomString(12));
        map->insert("album", Utils::randomString(10));
        map->insert("artist", Utils::randomString());
        map->insert("path", fileInfo.canonicalFilePath());
        map->insert("duration", 60));
#endif
    }
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
