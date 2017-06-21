#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>

#include "Artist.h"
#include "Album.h"
#include "TagLibWrapper.h"

class Album;
class Artist;

class Track : public QObject
{
        Q_OBJECT

    public:
        static const quint8 TRACK = 1;
        static const quint8 TITLE = 2;
        static const quint8 LYRICS = 4;

        explicit Track(QObject* parent = 0);
        Track(const Mp3Tags* tags, Album* album, QObject* parent = 0);
        Track(quint16 track, const QString& title, const QString& lyrics, quint16 year, quint32 m_duration, const QString& m_path, Album* album, QObject* parent = 0);

        Mp3Tags mp3Tags() const;

        quint16 track() const;
        void setTrack(quint8 track);

        const QString& title() const;
        void setTitle(const QString& title);

        const QString& lyrics() const;
        void setLyrics(const QString& lyrics);
        const QString& readLyrics(bool force = false);

        quint32 duration() const;
        void setDuration(quint32 duration);

        quint16 year() const;
        void setYear(quint8 year);

        QString path() const;
        void setPath(const QString& path);

        Album* album() const;
        void setAlbum(Album* album);

        Artist* artist() const;

    signals:
        void trackUpdated(Track* track, quint8 fields);
        void albumChanged(Album* album);
        void albumUpdated(Album* album, quint8);
        void artistUpdated(Artist* artist, quint8);

    private:
        QString m_title;
        quint16 m_track;
        quint32 m_year;

        quint32 m_bitrate;
        quint32 m_channels;
        quint32 m_duration;
        quint32 m_samplerate;

        QString m_lyrics;

        QString m_path;

        Album* m_album;
};

bool operator==(const Track& track1, const Track& track2);
bool operator<(const Track& track1, const Track& track2);

#endif// TRACK_H
