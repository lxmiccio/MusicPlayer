#ifndef ALBUM_H
#define ALBUM_H

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QVector>

#include "Artist.h"
#include "Track.h"

class Artist;
class Track;

class Album : public QObject
{
        Q_OBJECT

    public:
        static const quint8 TITLE = 1;
        static const quint8 COVER = 2;
        static const quint8 ARTIST = 4;

        explicit Album(QObject* parent = 0);
        explicit Album(const QString& title, Artist* artist, QObject* parent = 0);

        const QString& title() const;
        void setTitle(const QString& title);

        const QPixmap& cover() const;
        void setCover(const QPixmap& cover);

        const QVector<Track*>& tracks() const;
        Track* track(const QString& title) const;
        void addTrack(Track* track);
        bool removeTrack(Track* track);
        bool removeTrack(const QString& title);

        Artist* artist() const;
        void setArtist(Artist* artist);

        void sort();

    signals:
        void albumUpdated(Album* album, quint8 fields);
        void artistChanged(Artist* artist);
        void artistUpdated(Artist* artist, quint8 fields);
        void trackAdded(Track* track);
        void trackUpdated(Track* track, quint8);
        void trackRemoved(Track* track);

    private slots:
        void onArtistUpdated(Artist* artist, quint8 fields);

    private:
        QString m_title;
        QPixmap m_cover;
        Artist* m_artist;
        QVector<Track*> m_tracks;
};

bool operator==(const Album& album1, const Album& album2);
bool operator<(const Album& album1, const Album& album2);

#endif // ALBUM_H
