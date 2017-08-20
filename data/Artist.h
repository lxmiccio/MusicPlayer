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
        static const quint8 NAME = 1;
        static const quint8 IMAGE = 2;

        explicit Artist(QObject* parent = 0);
        explicit Artist(const QString& title, QObject* parent = 0);

        const QString& name() const;
        void setName(const QString& name);

        const QVector<Album*>& albums() const;
        Album* album(const QString& title) const;
        void addAlbum(Album* album);
        bool removeAlbum(Album* album);
        bool removeAlbum(const QString& title);

        const QVector<Track*> tracks() const;

        const QPixmap& image() const;
        void setImage(const QPixmap& image);
        void downloadImage();

        void sort();

    private slots:
        void onArtistInfoDownloaded(HttpRequestWorker* worker);
        void onImageDownloaded(HttpRequestWorker* worker);

    signals:
        void artistUpdated(Artist* artist, quint8 fields);
        void artistRemoved(Artist* artist);
        void albumAdded(Album* album);
        void albumUpdated(Album* album, quint8 fields);
        void albumRemoved(Album* album);

    private:
        QString m_name;
        QPixmap m_image;

        QVector<Album*> m_albums;
};

bool operator==(const Artist& artist1, const Artist& artist2);
bool operator<(const Artist& artist1, const Artist& artist2);

#endif// ARTIST_H
