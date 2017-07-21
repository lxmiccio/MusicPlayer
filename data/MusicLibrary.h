#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QMutex>
#include <QMutexLocker>
#include <QVector>

#include "Album.h"
#include "Artist.h"
#include "TagLibWrapper.h"
#include "Track.h"

class TrackLoader;

class MusicLibrary : public QObject
{
        Q_OBJECT

    public:
        static MusicLibrary* instance();
        static void deleteInstance();

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

        void changeArtistOnTrack(Track* track, QString newArtist);
        void changeAlbumOnTrack(Track* track, QString newAlbum);

    public slots:
        void onTracksToLoad(const QVector<QFileInfo>& filesInfo);
        void onArtistRemoved(Artist* artist);
        void onAlbumRemoved(Album* album);
        void onTrackRemoved(Track* track);

    signals:
        void artistAdded(Artist* artist);
        void artistRemoved(Artist* artist);
        void albumAdded(Album* album);
        void albumRemoved(Album* album);
        void trackAdded(Track* track);
        void trackRemoved(Track* track);

    protected:
        MusicLibrary();

    private slots:
        void onTrackLoaded(Track* p_track, QString p_artist, QString p_album);

    private:
        static MusicLibrary* m_instance;
        QVector<Artist*> m_artists;

        QMutex m_mutex;
};

#endif// MUSICLIBRARY_H
