#include "TagLibWrapper.h"


#include"qdebug.h"

class ImageFile : public TagLib::File
{
public:
    ImageFile(const char *file) : TagLib::File(file)
    {

    }

    TagLib::ByteVector data()
    {
        return readBlock(length());
    }


private:
    virtual TagLib::Tag *tag() const { return 0; }
    virtual TagLib::AudioProperties *audioProperties() const { return 0; }
    virtual bool save() { return false; }
};



QPixmap TagLibWrapper::readFlacCover(const QFileInfo &fileInfo)
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

QString TagLibWrapper::readFlacLyrics(const QFileInfo &fileInfo)
{
    Q_UNUSED(fileInfo);

    //TODO --> read .lrc file ifexists
    return QString();
}

void TagLibWrapper::readFlacTags(const QString& filename, Mp3Tags* tags)
{
    if(tags)
    {
        TagLib::FLAC::File file(filename.toStdString().data());

        if(file.isValid() && file.tag())
        {
            tags->album = file.tag()->album().toCString();
            tags->artist = file.tag()->artist().toCString();
            tags->title = file.tag()->title().toCString();
            tags->track = file.tag()->track();
            tags->year = file.tag()->year();

            tags->path = filename;

            if(file.audioProperties())
            {
                tags->bitrate = file.audioProperties()->bitrate();
                tags->channels = file.audioProperties()->channels();
                tags->duration = file.audioProperties()->lengthInSeconds();
                tags->samplerate = file.audioProperties()->sampleRate();
            }
        }
    }
}

QPixmap TagLibWrapper::readMp3Cover(const QFileInfo &fileInfo)
{
    TagLib::MPEG::File file(fileInfo.canonicalFilePath().toStdString().data());
    QPixmap cover;
    qDebug() << "hereee";

    if(file.ID3v2Tag())
    {
        TagLib::ID3v2::FrameList frameList = file.ID3v2Tag()->frameListMap()["APIC"];
        if(!frameList.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame* pictureFrame;
            for(TagLib::ID3v2::FrameList::ConstIterator i_frame = frameList.begin(); i_frame != frameList.end(); ++i_frame)
            {
                pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(*i_frame);
                cover = QPixmap::fromImage(QImage::fromData(QByteArray(pictureFrame->picture().data(), static_cast<int>(pictureFrame->picture().size()))));
                qDebug() << static_cast<int>(pictureFrame->type()) << pictureFrame->mimeType().toCString(true) << cover.width() << "x" << cover.height();
            }
        }
    }
    cover.save("prova.jpeg");
    return cover;
}

void TagLibWrapper::readMp3Lyrics(const QString& filename, Mp3Tags* tags)
{
    if(tags)
    {
        TagLib::MPEG::File file(filename.toStdString().data());

        if(file.ID3v2Tag())
        {
            TagLib::ID3v2::FrameList frameList = file.ID3v2Tag()->frameListMap()["USLT"];
            if(!frameList.isEmpty())
            {
                TagLib::ID3v2::UnsynchronizedLyricsFrame* frame = dynamic_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame*>(frameList.front());
                if(frame)
                {
                    QString lyrics = frame->text().toCString(true);
                    tags->lyrics = lyrics.replace("\r", "\r\n");
                }
            }
        }
    }
}

void TagLibWrapper::readMp3Tags(const QString& filename, Mp3Tags* tags)
{
    if(tags)
    {
        TagLib::FileRef fileRef(filename.toStdString().data());

        if(!fileRef.isNull() && fileRef.tag())
        {
            tags->album = fileRef.tag()->album().toCString();
            tags->artist = fileRef.tag()->artist().toCString();
            tags->title = fileRef.tag()->title().toCString();
            tags->track = fileRef.tag()->track();
            tags->year = fileRef.tag()->year();

            tags->path = filename;

            if(fileRef.audioProperties())
            {
                tags->bitrate = fileRef.audioProperties()->bitrate();
                tags->channels = fileRef.audioProperties()->channels();
                tags->duration = fileRef.audioProperties()->lengthInSeconds();
                tags->samplerate = fileRef.audioProperties()->sampleRate();
            }
        }
    }
}

void TagLibWrapper::setMp3Cover(const QString& filename, const QPixmap& cover)
{
    TagLib::MPEG::File* file = new TagLib::MPEG::File(filename.toUtf8().data());
    TagLib::ID3v2::Tag* tag = file->ID3v2Tag(true);

    TagLib::ID3v2::FrameList frames = tag->frameList("APIC");
    TagLib::ID3v2::AttachedPictureFrame* frame = 0;

    if(frames.isEmpty())
    {
        frame = new TagLib::ID3v2::AttachedPictureFrame;
    }
    else
    {
        frame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frames.front());
    }

    QString coverPath = "prova.jpeg";
    qDebug() << coverPath;
    cover.save(coverPath);

    ImageFile image(QFileInfo(coverPath).absoluteFilePath().toUtf8().data());

    frame->setDescription("Cover");
    frame->setMimeType("image/jpeg");
    frame->setPicture(image.data());
    frame->setType(TagLib::ID3v2::AttachedPictureFrame::Other);
    tag->addFrame(frame);

    file->save();
    delete file;
#if 0 /* works */
    TagLib::MPEG::File* file = new TagLib::MPEG::File(filename.toUtf8().data());
    TagLib::ID3v2::Tag *tag = file->ID3v2Tag(true);
    TagLib::ID3v2::FrameList frames = tag->frameList("APIC");
    TagLib::ID3v2::AttachedPictureFrame *frame = 0;

    for(int i = 0;  i <= 20;++i)
    {
        //    if(frames.isEmpty())
        //    {
        //        qDebug() << "isemty";
        frame = new TagLib::ID3v2::AttachedPictureFrame;
        //    }
        //    else
        //    {
        //        qDebug() << "notisemty";
        //        frame = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());
        //    }
        QString picname;
        if(i == 1)
        {
            QPixmap pixmap32 = QPixmap::fromImage(QImage("prova.jpeg")).scaled(32,
                                                                               32,
                                                                               Qt::KeepAspectRatio,
                                                                               Qt::SmoothTransformation);
            pixmap32.save("prova32.jpeg");
            picname = "prova32.jpeg";
            picname = "prova.jpeg";
        }
        else
        {
            picname = "prova.jpeg";
        }


        QFileInfo fi(picname);
        QFile f(picname);
        f.setf
                qDebug() << fi.absoluteFilePath();

        ImageFile image(fi.absoluteFilePath().toUtf8().data());

        frame->setPicture(image.data());
        frame->setDescription("Cover");
        frame->setType(static_cast<TagLib::ID3v2::AttachedPictureFrame::Type>(i));
        frame->setMimeType("image/jpeg");
        qDebug() << "isem"<< frame->picture().isEmpty();
        tag->addFrame(frame);

        qDebug() << file->save();
        qDebug() << file->save();
        qDebug() << file->save();
        qDebug() << file->save();
    }


    delete file;
#endif
#if 0 /* Not working */
    TagLib::MPEG::File file(filename.toStdString().data());

    if(file.ID3v2Tag())
    {
        TagLib::ID3v2::FrameList frameList = file.ID3v2Tag()->frameListMap()["APIC"];
        if(frameList.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame* frame = new TagLib::ID3v2::AttachedPictureFrame();
            frame->setData(cover.toImage().bits());
            //            frame->setPicture(...);
            frame->setDescription("Cover");
            frame->setMimeType("image/jpeg");
            frame->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);

            file.ID3v2Tag()->addFrame(frame);

            /* Taglib takes care of deleting frame */
        }

        file.ID3v2Tag()->save();
    }
#endif
}

void TagLibWrapper::setMp3Tags(const QString& filename, const Mp3Tags tags)
{
    /* Doing so because TagLib::FileRef must be destroyed before opening TagLib::MPEG::File */
    {
        TagLib::FileRef fileRef(filename.toStdString().data());

        if(!fileRef.isNull() && fileRef.tag())
        {
            fileRef.tag()->setArtist(tags.artist.toStdString().data());
            fileRef.tag()->setAlbum(tags.album.toStdString().data());
            fileRef.tag()->setTrack(tags.track);
            fileRef.tag()->setTitle(tags.title.toStdString().data());
            fileRef.save();
        }
    }

    TagLib::MPEG::File file(filename.toStdString().data());

    if(file.ID3v2Tag())
    {
        TagLib::ID3v2::FrameList frameList = file.ID3v2Tag()->frameListMap()["USLT"];
        if(!frameList.isEmpty())
        {
            TagLib::ID3v2::UnsynchronizedLyricsFrame* frame = dynamic_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame*>(frameList.front());
            if(frame)
            {
                frame->setText(QString(tags.lyrics).replace("\r\n", "\r").toStdString().data());
            }
        }
        else
        {
            TagLib::ID3v2::UnsynchronizedLyricsFrame* frame = new TagLib::ID3v2::UnsynchronizedLyricsFrame("USLT");
            frame->setText(QString(tags.lyrics).replace("\r\n", "\r").toStdString().data());

            file.ID3v2Tag()->addFrame(frame);

            /* Taglib takes care of deleting frame */
        }

        file.save();
    }
}

QString TagLibWrapper::extensionToMimetype(const QString& extension)
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
