#ifndef ARTIST_H
#define ARTIST_H

#include <QString>
#include <QVector>

#include "album.h"
#include "track.h"

class Album;

class Artist
{
    public:
        explicit Artist();
        explicit Artist(const QString &title);

        const QString& name() const;
        void setName(const QString& name);

        const QVector<Album*>& albums() const;
        const Album* album(const QString& title) const;
        void addAlbum(Album& album);
        bool removeAlbum(Album& album);
        bool removeAlbum(const QString& title);

        const QVector<Track*>& tracks() const;

    private:
        QVector<Album*> m_albums;

        QString m_name;
};

bool operator==(const Artist& artist1, const Artist& artist2);

#endif // ARTIST_H
