#include "loadplaylistwindow.h"

#include "QDebug"
#include "QDir"
#include "QListWidgetItem"

#include "playlist.h"

LoadPlaylistWindow::LoadPlaylistWindow(StackedWidget* stackedWidget, QWidget* parent) : QWidget(parent)
{
  this->stackedWidget = stackedWidget;

  this->playlists = new QListWidget();
  this->playlists->addItems(Playlist::getAllPlaylists(QDir::currentPath() + "/tracks/"));

  this->goBack = new QPushButton("Go Back");
  QObject::connect(this->goBack, SIGNAL(clicked()), this->stackedWidget, SLOT(previousView()));

  this->loadPlaylist = new QPushButton("Load");
  QObject::connect(this->loadPlaylist, SIGNAL(clicked()), this, SLOT(loadPlaylistClicked()));

  QGridLayout* gridLayout = new QGridLayout();

  gridLayout->addWidget(this->playlists, 0, 0, 1, 2);
  gridLayout->addWidget(this->goBack, 1, 0, 1, 1);
  gridLayout->addWidget(this->loadPlaylist, 1, 1, 1, 1);

  setLayout(gridLayout);
}

void LoadPlaylistWindow::loadPlaylistClicked()
{
  if(this->playlists->currentRow() != -1) {
    emit(playlistLoaded(this->playlists->currentItem()->text()));

    this->stackedWidget->previousView();
  }
}
