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
        explicit Album(QObject* parent = 0);
        explicit Album(const QString& title, Artist* artist, QObject* parent = 0);

        const QString& title() const;
        void setTitle(const QString& title);

        const QPixmap& cover() const;
        void setCover(const QPixmap& cover);

        const QVector<Track*>& tracks() const;
        const Track* track(const QString& title) const;
        void addTrack(Track* track);
        bool removeTrack(Track* track);
        bool removeTrack(const QString& title);

        Artist* artist() const;
        void setArtist(Artist* artist);

    signals:
        void trackAdded(Track& track);
        void trackRemoved(Track& track);

    private:
        QString m_title;
        QPixmap m_cover;
        Artist* m_artist;
        QVector<Track*> m_tracks;
};

bool operator==(const Album& album1, const Album& album2);
bool operator<(const Album& album1, const Album& album2);

#endif // ALBUM_H
