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
        Track(quint16 track, const QString& title, const QString& lyrics, quint16 year, quint32 m_duration, const QString& m_path, const Album* album);

        quint16 track() const;
        void setTrack(quint8 track);

        const QString& title() const;
        void setTitle(const QString& title);

        const QString& lyrics() const;
        void setLyrics(const QString& lyrics);

        quint16 year() const;
        void setYear(quint8 year);

        quint32 duration() const;
        void setDuration(quint32 duration);

        const QString& path() const;
        void setPath(const QString& path);

        const Album* album() const;
        void setAlbum(Album& album);

        const Artist* artist() const;

    private:
        const Album* c_album;

        quint16 m_track;
        QString m_title;
        QString m_lyrics;
        quint16 m_year;
        quint32 m_duration;
        QString m_path;
};

bool operator==(const Track& track1, const Track& track2);
bool operator<(const Track& track1, const Track& track2);

#endif // TRACK_H
