#ifndef ARTIST_H
#define ARTIST_H

#include <QObject>
#include <QString>
#include <QVector>

#include "Album.h"
#include "Track.h"

class Album;

class Artist : public QObject
{
        Q_OBJECT

    public:
        explicit Artist(QObject* parent = 0);
        explicit Artist(const QString &title, QObject* parent = 0);

        const QString& name() const;
        void setName(const QString& name);

        const QVector<Album*>& albums() const;
        Album* album(const QString& title) const;
        void addAlbum(Album* album);
        bool removeAlbum(Album* album);
        bool removeAlbum(const QString& title);

        const QVector<Track*> tracks() const;

    signals:
        void albumAdded(Album& album);
        void albumRemoved(Album& album);

    private:
        QVector<Album*> m_albums;
        QString m_name;
};

bool operator==(const Artist& artist1, const Artist& artist2);
bool operator<(const Artist& artist1, const Artist& artist2);

#endif // ARTIST_H
