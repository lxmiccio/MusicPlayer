#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QString>
#include <QVariantMap>

#include "Artist.h"
#include "Album.h"

class Album;
class Artist;

class Track : public QObject
{
    public:
        explicit Track(QObject* parent = 0);
        Track(const QVariantMap& tags, Album* album, QObject* parent = 0);
        Track(quint16 track, const QString& title, const QString& lyrics, quint16 year, quint32 m_duration, const QString& m_path, Album* album, QObject* parent = 0);

        quint16 track() const;
        void setTrack(quint8 track);

        const QString& title() const;
        void setTitle(const QString& title);

        quint32 duration() const;
        void setDuration(quint32 duration);

        quint16 year() const;
        void setYear(quint8 year);

        const QString& lyrics() const;
        void setLyrics(const QString& lyrics);

        const QString& path() const;
        void setPath(const QString& path);

        Album* album() const;
        void setAlbum(Album* album);

        Artist* artist() const;

    private:
        quint16 m_track;
        QString m_title;
        QString m_lyrics;
        quint16 m_year;
        quint32 m_duration;
        QString m_path;
        Album* m_album;
};

bool operator==(const Track& track1, const Track& track2);
bool operator<(const Track& track1, const Track& track2);

#endif // TRACK_H
