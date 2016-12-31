#ifndef TRACK_H
#define TRACK_H

#include <QMediaContent>
#include <QPixmap>
#include <QString>

#include "artist.h"
#include "album.h"

class Album;
class Artist;

class Track
{
    public:
        explicit Track();
        Track(const QVariantMap& tags, const Album* album);

        const QString& title() const;
        void setTitle(const QString& title);

        const QPixmap& cover() const;
        void setCover(const QPixmap& cover);

        const QString& lyrics() const;
        void setLyrics(const QString& lyrics);

        quint8 track() const;
        void setTrack(quint8 track);

        quint8 year() const;
        void setYear(quint8 year);

        quint32 duration() const;
        QString durationInMinutes() const;
        void setDuration(quint32 duration);

        quint32 bitrate() const;
        void setBitrate(quint32 bitrate);

        const QString& url() const;
        void setUrl(const QString& url);

        quint64 size() const;
        void setSize(quint64 size);

        const QMediaContent& mediaContent() const;
        void setMediaContent(const QMediaContent& mediaContent);

        const Album* album() const;
        void setAlbum(Album& album);

        const Artist *artist() const;

        static bool isSupportedSuffix(const QString& suffix);

    private:
        const Album* c_album;

        QString m_title;
        QPixmap m_cover;
        QString m_lyrics;
        quint8 m_track;
        quint8 m_year;
        quint32 m_duration;
        quint32 m_bitrate;

        QString m_url;
        quint64 m_size;

        QMediaContent m_mediaContent;
};

bool operator==(const Track& track1, const Track& track2);
bool operator<(const Track& track1, const Track& track2);

#endif // TRACK_H
