#ifndef SAVEPLAYLISTWINDOW_H
#define SAVEPLAYLISTWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "playlist.h"
#include "StackedWidget.h"

class SavePlaylistWindow : public QWidget
{
  Q_OBJECT

protected:
  StackedWidget* stackedWidget;
  Playlist* playlist;
  QLabel* playlistName;
  QLineEdit* name;
  QPushButton* goBack;
  QPushButton* savePlaylist;

public:
  SavePlaylistWindow(StackedWidget* stackedWidget, Playlist* playlist, QWidget* parent = 0);

public slots:
  void savePlaylistClicked();
};

#endif // SAVEPLAYLISTWINDOW_H
