#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "AlbumView.h"
#include "ArtistView.h"
#include "AudioControls.h"
#include "AudioEngine.h"
#include "BackgroundWidget.h"
#include "ImageButton.h"
#include "MusicLibrary.h"
#include "ScrollableArea.h"
#include "MainWindow.h"
#include "TagUtils.h"
#include "Track.h"
#include "TrackDelegate.h"
#include "TrackItem.h"
#include "TrackLoader.h"
#include "TrackView.h"

class MainWidget : public BackgroundWidget
{
        Q_OBJECT

    public:
        MainWidget(QWidget* parent = 0);
        ~MainWidget();

    public slots:
        void onShowArtistViewTriggered();
        void onShowAlbumViewTriggered();
        void onCoverClicked(const Album& album);
        void onItemDoubleClicked(const Track& track);
        void onTrackStarted(const Track& track);
        void onCurrentTrackClicked();
        void coverClicked();

    signals:
        void trackClicked(const Track& track);
        void trackAdded(const Track& track);
        void trackStarted(const Track& track);

    public:
        const MainWindow* c_mainWindow;

        AlbumView* m_albumView;
        ArtistView* m_artistView;
        ScrollableArea* m_scrollableArea;

        TrackView* m_trackView;

        AudioControls* m_audioControls;
        AudioEngine* m_audioEngine;

        QHBoxLayout* m_horLayout;
        QVBoxLayout* m_layout;

        MusicLibrary* m_musicLibrary;
        TrackLoader* m_trackLoader;
};

#endif // MAINWIDGET_H
