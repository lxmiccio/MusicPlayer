#include "Artist.h"

#include <QDir>

Artist::Artist(QObject* parent) : QObject(parent)
{
}

Artist::Artist(const QString& name, QObject* parent) : QObject(parent)
{
    m_name = name;

    if(isImageAvailable(m_name))
    {
        m_image = readImage(m_name);
    }
    else
    {
        downloadImage();
    }
}

const QString& Artist::name() const
{
    return m_name;
}

void Artist::setName(const QString& name)
{
    m_name = name;
    emit artistUpdated(this, Artist::NAME);
}

const QVector<Album*>& Artist::albums() const
{
    return m_albums;
}

Album* Artist::album(const QString& title) const
{
    foreach(Album* i_album, m_albums)
    {
        if(i_album->title() == title)
        {
            return i_album;
        }
    }

    return NULL;
}

void Artist::addAlbum(Album* album)
{
    if(album)
    {
        QObject::connect(album, SIGNAL(albumUpdated(Album*, quint8)), this, SIGNAL(albumUpdated(Album*, quint8)));
        m_albums.push_back(album);

        sort();
        emit albumAdded(album);
    }
}

bool Artist::removeAlbum(Album* album)
{
    if(m_albums.removeOne(album))
    {
        emit albumRemoved(album);

        delete album;
        album = NULL;

        if(m_albums.isEmpty())
        {
            emit artistRemoved(this);
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool Artist::removeAlbum(const QString& title)
{
    foreach(Album* i_album, m_albums)
    {
        if(i_album->title() == title)
        {
            return removeAlbum(i_album);
        }
    }

    return false;
}

const QVector<Track*> Artist::tracks() const
{
    QVector<Track*> tracks;

    foreach(Album* i_album, m_albums)
    {
        foreach(Track* i_track, i_album->tracks())
        {
            tracks.push_back(i_track);
        }
    }

    return tracks;
}

const QPixmap& Artist::image() const
{
    return m_image;
}

void Artist::setImage(const QPixmap& image)
{
    m_image = image;
}

void Artist::downloadImage()
{
    HttpRequestWorker* worker = new HttpRequestWorker();
    QObject::connect(worker, SIGNAL(requestFinished(HttpRequestWorker*)), this, SLOT(onArtistInfoDownloaded(HttpRequestWorker*)));
    worker->artistInfoLastFm(m_name);
}

void Artist::sort()
{
    std::sort(m_albums.begin(), m_albums.end(), [] (const Album* album1, const Album* album2) -> bool
    {
        return album1->title() < album2->title();
    });
}

void Artist::onArtistInfoDownloaded(HttpRequestWorker* worker)
{
    if(!worker->isError())
    {
        QString url = worker->imageUrl();
        if(!url.isEmpty())
        {
            HttpRequestInput input(url);

            HttpRequestWorker* newWorker = new HttpRequestWorker();
            QObject::connect(newWorker, SIGNAL(requestFinished(HttpRequestWorker*)), this, SLOT(onImageDownloaded(HttpRequestWorker*)));
            newWorker->execute(input);
        }
        else
        {
            qDebug() << "Url is empty";
        }
    }
    else
    {
        qDebug() << "Http request failed with error" << worker->errorMessage();
    }

    worker->deleteLater();
}

void Artist::onImageDownloaded(HttpRequestWorker* worker)
{
    if(!worker->isError())
    {
        m_image.loadFromData(worker->response());
        emit artistUpdated(this, IMAGE);

        saveImage(m_name, m_image);

        qDebug() << "Image downloaded for artist" << m_name;
    }
    else
    {
        qDebug() << "Http request failed with error" << worker->errorMessage();
    }

    worker->deleteLater();
}

bool Artist::isImageAvailable(const QString& name)
{
    return QFile("artists/" + name + ".png").exists();
}

QPixmap Artist::readImage(const QString& name)
{
    QPixmap pixmap;
    pixmap.load("artists/" + name + ".png");

    return pixmap;
}

void Artist::saveImage(const QString& name, const QPixmap& image)
{
    if(!QDir("artists").exists())
    {
        QDir().mkpath("artists");
    }

    QFile file("artists/" + name + ".png");
    file.open(QIODevice::WriteOnly);

    image.save(&file, "PNG");
}

bool operator==(const Artist& artist1, const Artist& artist2)
{
    return artist1.name() == artist2.name();
}

bool operator<(const Artist& artist1, const Artist& artist2)
{
    return artist1.name() < artist2.name();
}
