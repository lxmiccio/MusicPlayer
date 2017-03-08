#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QVector>

#include "Album.h"
#include "Artist.h"
#include "Track.h"

class MusicLibrary : public QObject
{
        Q_OBJECT

    public:
        static MusicLibrary* instance();

        const QVector<Artist*>& artists() const;
        Artist* artist(const QString& name) const;
        bool removeArtist(Artist* artist);
        bool removeArtist(const QString& name);

        const QVector<Album*> albums() const;
        Album* album(const QString& title) const;
        Album* album(const QString& title, const QString& artistName) const;
        bool removeAlbum(Album* album);
        bool removeAlbum(const QString& albumName, const QString &artistName);

        const QVector<Track*> tracks() const;
        bool removeTrack(Track* track);
        bool removeTrack(const QString& trackTitle, const QString& albumTitle);

        Track* addTrack(QVariantMap& tags);

    signals:
        void artistAdded(const Artist* artist);
        void albumAdded(const Album* album);
        void trackAdded(const Track* track);

    protected:
        MusicLibrary();

    private:
        static QPointer<MusicLibrary> m_instance;
        QVector<Artist*> m_artists;

        QMutex m_mutex;
};

#endif // MUSICLIBRARY_H
