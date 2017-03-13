#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AudioControls.h"
#include "AudioEngine.h"
#include "AlbumView.h"
#include "artistview/ArtistView.h"
#include "BackgroundWidget.h"
#include "ImageButton.h"
#include "MusicLibrary.h"
#include "ScrollableArea.h"
#include "StackedWidget.h"
#include "TagUtils.h"
#include "Track.h"
#include "TrackDelegate.h"
#include "TrackItem.h"
#include "TrackLoader.h"
#include "TrackView.h"

class MainWindow : public BackgroundWidget
{
        Q_OBJECT

    private:
        const StackedWidget* c_stackedWidget;

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

    public:
        MainWindow(const StackedWidget* stackedWidget, QWidget* parent = 0);

    public slots:
        void onCoverClicked(const Album& album);
        void onItemDoubleClicked(const Track& track);
        void onTrackStarted(const Track& track);
        void coverClicked();

    signals:
        void trackClicked(const Track& track);
        void trackAdded(const Track& track);
        void trackStarted(const Track& track);
};

#endif // MAINWINDOW_H
