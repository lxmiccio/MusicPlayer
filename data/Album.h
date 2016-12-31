#ifndef ALBUM_H
#define ALBUM_H

#include <QPixmap>
#include <QString>
#include <QVector>

#include "Artist.h"
#include "Track.h"

class Artist;
class Track;

class Album
{
    public:
        explicit Album();
        explicit Album(const QString& title, const Artist* artist);

        const QString& title() const;
        void setTitle(const QString& title);

        const QPixmap& cover() const;
        void setCover(const QPixmap& cover);

        const QVector<Track*>& tracks() const;
        const Track* track(const QString& title) const;
        void addTrack(Track& track);
        bool removeTrack(Track& track);
        bool removeTrack(const QString& title);

        const Artist* artist() const;
        void setArtist(const Artist& artist);

    private:
        const Artist* c_artist;

        QVector<Track*> m_tracks;

        QString m_title;
        QPixmap m_cover;
};

bool operator==(const Album& album1, const Album& album2);

#endif // ALBUM_H
