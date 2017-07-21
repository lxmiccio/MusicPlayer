#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>

#include "Artist.h"
#include "Album.h"
#include "HttpRequestInput.h"
#include "HttpRequestWorker.h"
#include "Settings.h"
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
        Track(const QString& path, QObject* parent = 0);

        void load(bool asynchronous = true);

        Mp3Tags mp3Tags() const;

        quint16 track() const;
        void setTrack(quint8 track);

        const QString& title() const;
        void setTitle(const QString& title);

        const QString& lyrics() const;
        void setLyrics(const QString& lyrics);
        const QString& readLyrics(bool force = false);
        void downloadLyrics();

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
        void loadTrack();
        void trackLoaded(Track* track, QString artist, QString album);
        void trackUpdated(Track* track, quint8 fields);
        void albumChanged(Album* album);
        void albumUpdated(Album* album, quint8);
        void artistUpdated(Artist* artist, quint8);

    private slots:
        void onLoadTrack();
        void onLyricsUrlFound(HttpRequestWorker* worker);
        void onLyricsDownloaded(HttpRequestWorker* worker);

    private:
        Mp3Tags m_tags;
        Album* m_album;
};

bool operator==(const Track& track1, const Track& track2);
bool operator<(const Track& track1, const Track& track2);

#endif// TRACK_H
