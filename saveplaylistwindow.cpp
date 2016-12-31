#include "saveplaylistwindow.h"

#include <QDebug>
#include <QDir>
#include <QGridLayout>
#include <QMessageBox>

SavePlaylistWindow::SavePlaylistWindow(StackedWidget* stackedWidget, Playlist* playlist, QWidget* parent) : QWidget(parent)
{
  this->stackedWidget = stackedWidget;
  this->playlist = playlist;

  this->playlistName = new QLabel("Enter Playlist name: ");

  this->name = new QLineEdit();

  this->goBack = new QPushButton("Go Back");
  QObject::connect(this->goBack, SIGNAL(clicked()), this->stackedWidget, SLOT(previousView()));

  this->savePlaylist = new QPushButton("Save");
  QObject::connect(this->savePlaylist, SIGNAL(clicked()), this, SLOT(savePlaylistClicked()));

  QGridLayout* gridLayout = new QGridLayout();

  gridLayout->addWidget(this->playlistName, 0, 0, 1, 1);
  gridLayout->addWidget(this->name, 0, 1, 1, 1);
  gridLayout->addWidget(this->goBack, 1, 0, 1, 1);
  gridLayout->addWidget(this->savePlaylist, 1, 1, 1, 1);

  setLayout(gridLayout);
}

void SavePlaylistWindow::savePlaylistClicked()
{
  if(not QDir("tracks").exists()) {
    QDir().mkdir("tracks");
  }

  QString path {QDir::currentPath() + "/tracks/"};
  QString playlistName {this->name->text()};
  QString playlistPath {path + playlistName};

  if(QDir(playlistPath).exists()) {
    QMessageBox messageBox;
    messageBox.setText("Overwrite the existing playlist?");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);

    switch(messageBox.exec()) {
    case QMessageBox::Yes: {
      QDir directory {playlistPath};

      directory.setFilter( QDir::NoDotAndDotDot | QDir::Files );
      for(QStringList::iterator files {directory.entryList().begin()}; files != directory.entryList().end(); ++files) {
        directory.remove(*files);
      }

      directory.setFilter( QDir::NoDotAndDotDot | QDir::Dirs );
      for(QStringList::iterator files {directory.entryList().begin()}; files != directory.entryList().end(); ++files) {
        QDir subDirectory {directory.absoluteFilePath(*files)};
        subDirectory.removeRecursively();
      }

      this->playlist->savePlaylist(playlistPath);

      break;
    }
    case QMessageBox::No:

      break;
    }
  }
  else {
    if(QDir().mkdir(playlistPath)) {
      this->playlist->savePlaylist(playlistPath);
    }
    else {
      qDebug() << "Cannot create directory " << playlistName << " in " << path;
    }
  }

  this->stackedWidget->previousView();
}
