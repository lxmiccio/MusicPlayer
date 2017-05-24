#ifndef AUDIOCONTROLS_H
#define AUDIOCONTROLS_H

#include <QApplication>
#include <QHBoxLayout>
#include <QHotkey>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "BackgroundWidget.h"
#include "ClickableLabel.h"
#include "ImageButton.h"
#include "ImageUtils.h"
#include "TrackSlider.h"
#include "Settings.h"
#include "Slider.h"
#include "Track.h"
#include "Utils.h"

class AudioControls : public QWidget
{
        Q_OBJECT

    public:
        explicit AudioControls(QWidget* parent = 0);
        ~AudioControls();

        typedef enum ShuffleMode
        {
            SHUFFLE_OFF = 0,
            SHUFFLE_ON
        }
        ShuffleMode_t;

        typedef enum RepeatMode
        {
            REPEAT_NONE = 0,
            REPEAT_ONE,
            REPEAT_ALL
        }
        RepeatMode_t;

        typedef enum VolumeMode
        {
            VOLUME_MUTED = 0,
            VOLUME_NOT_MUTED
        }
        VolumeMode_t;

    public slots:
        void onPositionChanged(qint64 position);
        void onTrackStarted(Track* Track);
        void onTrackFinished();

    private slots:
        void onBackwardClicked();
        void onPlayClicked();
        void onPauseClicked();
        void onForwardClicked();
        void onTrackValueChanged(int value);
        void onShuffleClicked();
        void onRepeatClicked();
        void onVolumeClicked();
        void onVolumeValueChanged(int value);

    signals:
        void trackStarted(int duration);
        void trackFinished();
        void currentTrackClicked();
        void backwardClicked();
        void playClicked();
        void pauseClicked();
        void forwardClicked();
        void positionChanged(qint64 position);
        void trackValueChanged(int position);
        void shuffleClicked(AudioControls::ShuffleMode_t shuffleMode);
        void repeatClicked(AudioControls::RepeatMode_t repeatMode);
        void volumeClicked(AudioControls::VolumeMode_t volumeMode);
        void volumeValueChanged(int value);

    private:
        Track* m_currentTrack;

        RepeatMode_t m_repeatMode;
        ShuffleMode_t m_shuffleMode;
        VolumeMode_t m_volumeMode;

        QHotkey m_volumeShortcut;

        QVBoxLayout* m_verticalLayout;

        QHBoxLayout* m_upperHorizontalLayout;
        QSpacerItem* m_upperSpacer1;
        ClickableLabel* m_artist;
        QLabel* m_dash;
        ClickableLabel* m_track;
        QSpacerItem* m_upperSpacer2;

        QHBoxLayout* m_lowerHorizontalLayout;
        ImageButton* m_backward;
        QSpacerItem* m_lowerSpacer1;
        ImageButton* m_play;
        ImageButton* m_pause;
        QSpacerItem* m_lowerSpacer2;
        ImageButton* m_forward;
        QSpacerItem* m_lowerSpacer3;
        QLabel* m_elapsedTime;
        QSpacerItem* m_lowerSpacer4;
        TrackSlider* m_trackSlider;
        QSpacerItem* m_lowerSpacer5;
        QLabel* m_remainingTime;
        QSpacerItem* m_lowerSpacer6;
        ImageButton* m_shuffle;
        QSpacerItem* m_lowerSpacer7;
        ImageButton* m_repeat;
        QSpacerItem* m_lowerSpacer8;
        ImageButton* m_volume;
        Slider* m_volumeSlider;
};

#endif // AUDIOCONTROLS_H
