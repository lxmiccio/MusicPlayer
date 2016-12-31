#include "playlist.h"

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QDebug>

Playlist::Playlist()
{
  this->tracks = QVector<Track>();
}

void Playlist::setName(QString name)
{
  this->name = name;
}

QString Playlist::getName()
{
  return this->getName();
}

QVector<Track>* Playlist::getTracks()
{
  return &this->tracks;
}

void Playlist::addTrack(Track track)
{
  this->tracks.push_back(track);
}

void Playlist::removeTrack(Track &track)
{
  this->tracks.removeAt(this->tracks.indexOf(track));
}

void Playlist::removeAllTracks()
{
  this->tracks.empty();
}

void Playlist::savePlaylist(QString path)
{
  for(QVector<Track>::iterator track {this->tracks.begin()}; track != this->tracks.end(); ++track) {
    //QFile::copy(track->getPath(), path + '/' + track->getFilename());
  }
}

Playlist Playlist::loadPlaylist(QString path)
{
  QDir directory {path};

  QStringList filenames = directory.entryList(QStringList() << "*.mp3", QDir::Files);

  Playlist playlist = Playlist();

  playlist.setName(QString(path.split('/').last()));

  for(QStringList::iterator filename {filenames.begin()}; filename != filenames.end(); ++filename) {
    QFileInfo fileInfo {*filename};
    QStringList data {directory.filePath(*filename).split('/')};

    QString title = QString(data.at(data.length() - TITLE_INDEX)).mid(5);
    title = title.left(title.length() - 4);

    //Track track = Track(QString(data.at(data.length() - ARTIST_INDEX)), QString(data.at(data.length() - ALBUM_INDEX)), title, QString(data.at(data.length() - TITLE_INDEX)), directory.filePath(*filename), QUrl::fromLocalFile(fileInfo.absoluteFilePath()));

    //playlist.addTrack(track);
  }

  return playlist;
}

QStringList Playlist::getAllPlaylists(QString path)
{
  QStringList playlists;

  QDirIterator directories {path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories};

  while(directories.hasNext()) {
    directories.next();

    playlists.push_back(directories.fileName());
  }

  return playlists;
}
