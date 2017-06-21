#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "AlbumView.h"
#include "ArtistView.h"
#include "AudioControls.h"
#include "AudioEngine.h"
#include "BackgroundWidget.h"
#include "ImageUtils.h"
#include "MainWindow.h"
#include "ScrollableArea.h"
#include "Settings.h"
#include "Track.h"
#include "PlayingView.h"

class MainWidget : public BackgroundWidget
{
        Q_OBJECT

    public:
        MainWidget(QWidget* parent = 0);
        ~MainWidget();

    public slots:
        void onShowArtistViewTriggered();
        void onShowAlbumViewTriggered();
        void onShowTrackViewTriggered();
        void onCoverClicked(Album* album);
        void onTrackStarted(Track* track);
        void onCurrentTrackClicked();
        void coverClicked();
        void onTrackDoubleClicked(Track* track);

    signals:
        void trackStarted(Track* track);

    private:
        void showView(Settings::View view);

        const MainWindow* c_mainWindow;

        AudioControls* m_audioControls;
        AudioEngine* m_audioEngine;

        Settings::View m_previousView;
        Settings::View m_currentView;
        AlbumView* m_albumView;
        ArtistView* m_artistView;
        ScrollableArea* m_scrollableTrackView;
        TrackView* m_trackView;
        PlayingView* m_playingView;

        QHBoxLayout* m_horLayout;
        QVBoxLayout* m_layout;
};

#endif// MAINWIDGET_H
