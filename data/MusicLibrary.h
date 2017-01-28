#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

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
        bool removeArtist(Artist& artist);
        bool removeArtist(const QString& name);

        const QVector<Album*>& albums() const;
        Album* album(const QString& title) const;
        bool removeAlbum(Album& album);
        bool removeAlbum(const QString& albumName, const QString &artistName);

        const QVector<Track*>& tracks() const;
        bool removeTrack(Track& track);
        bool removeTrack(const QString& trackTitle, const QString& albumTitle);

        Track* addTrack(const QVariantMap& tags);

    protected:
        MusicLibrary();

    private:
        static QPointer<MusicLibrary> m_instance;
        QVector<Artist*> m_artists;
};

#endif // MUSICLIBRARY_H
