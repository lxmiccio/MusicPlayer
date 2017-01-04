#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QVector>
#include <QVBoxLayout>



#include "AudioEngine.h"
#include "playlist.h"
#include "Track.h"
#include "MusicLibrary.h"

#include "TagUtils.h"

#include "TrackDelegate.h"
#include "TrackItem.h"
#include "TrackView.h"

#include "AlbumView.h"
#include "ScrollArea.h"

#include "ImageButton.h"
#include "StackedWidget.h"
#include "BackgroundWidget.h"

#include <QStandardItemModel>

#include <LeftPanel.h>

class MainWindow : public BackgroundWidget
{
    Q_OBJECT

private:
    const StackedWidget* c_stackedWidget;

    AlbumView* m_albumView;
    ScrollArea* m_scrollArea;

    TrackView* m_trackView;

    AudioEngine* m_audioEngine;

    QHBoxLayout* m_horLayout;
    QVBoxLayout* m_layout;

    MusicLibrary* m_musicLibrary;

    MusicPlayer* m_musicPlayer;

    LeftPanel* m_leftPanel;

public:
    MainWindow(const StackedWidget* stackedWidget, QWidget* parent = 0);

public slots:
    void onCoverClicked(const Album& album);

    void onFileDropped(const QFileInfo& fileInfo);
    void coverClicked();

    void itemDoubleClicked(const Track& track);

signals:
    void trackClicked(const Track& track);
    void trackAdded(const Track& track);
};

#endif // MAINWINDOW_H
