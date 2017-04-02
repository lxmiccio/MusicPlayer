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
#include "Settings.h"
#include "Track.h"
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
        void onShowTrackViewTriggered();
        void onCoverClicked(const Album& album);
        void onItemDoubleClicked(const Track& track);
        void onTrackStarted(const Track& track);
        void onCurrentTrackClicked();
        void coverClicked();

    signals:
        void trackClicked(const Track& track);
        void trackAdded(const Track& track);
        void trackStarted(const Track& track);

    private:
        void showView(Settings::View view);

        const MainWindow* c_mainWindow;

        AudioControls* m_audioControls;
        AudioEngine* m_audioEngine;

        Settings::View m_currentView;
        AlbumView* m_albumView;
        ArtistView* m_artistView;
        TrackView* m_trackView;
        TrackView* m_playingView;

        QHBoxLayout* m_horLayout;
        QVBoxLayout* m_layout;
};

#endif // MAINWIDGET_H
