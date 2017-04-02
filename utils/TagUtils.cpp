#include "TagUtils.h"

QPixmap TagUtils::readFlacCover(const QFileInfo &fileInfo)
{
    TagLib::FLAC::File file(fileInfo.canonicalFilePath().toStdString().data());
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
        TagLib::FLAC::File file(fileInfo.canonicalFilePath().toStdString().data());

        if(file.isValid() && file.tag())
        {
            map->insert("track", file.tag()->track());
            map->insert("title", file.tag()->title().toCString(true));
            map->insert("album", file.tag()->album().toCString(true));
            map->insert("artist", file.tag()->artist().toCString(true));
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
    TagLib::MPEG::File file(fileInfo.canonicalFilePath().toStdString().data());
    QPixmap cover;

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

void TagUtils::readMp3Lyrics(const QFileInfo &fileInfo, QVariantMap* map)
{
    if(map)
    {
        TagLib::MPEG::File file(fileInfo.canonicalFilePath().toStdString().data());
        QString lyrics;

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
                    map->insert("lyrics", lyrics);
                }
            }
        }
    }
}

void TagUtils::readMp3Tags(const QFileInfo &fileInfo, QVariantMap* map)
{
    if(map)
    {
#ifndef DEBUG
        TagLib::FileRef fileRef(fileInfo.canonicalFilePath().toStdString().data());

        if(!fileRef.isNull() && fileRef.tag())
        {
            map->insert("track", fileRef.tag()->track());
            map->insert("title", fileRef.tag()->title().toCString(true));
            map->insert("album", fileRef.tag()->album().toCString(true));
            map->insert("artist", fileRef.tag()->artist().toCString(true));
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
