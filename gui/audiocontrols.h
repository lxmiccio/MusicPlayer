#ifndef AUDIOCONTROLS_H
#define AUDIOCONTROLS_H

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "BackgroundWidget.h"
#include "ImageButton.h"
#include "SeekSlider.h"
#include "Track.h"

namespace AC
{
}

class AudioControls : public QWidget
{
  Q_OBJECT

  public:
    explicit AudioControls(QWidget* parent = 0);
    ~AudioControls();

    void showPlay(bool show);
    void showPause(bool show);

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

  private:
    QVBoxLayout* m_verticalLayout;

    QHBoxLayout* m_upperHorizontalLayout;
    QSpacerItem* m_upperSpacer1;
    QLabel* m_artist;
    QLabel* m_dash;
    QLabel* m_track;
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
    SeekSlider* m_musicSlider;
    QSpacerItem* m_lowerSpacer5;
    QLabel* m_remainingTime;
    QSpacerItem* m_lowerSpacer6;
    ImageButton* m_shuffle;
    QSpacerItem* m_lowerSpacer7;
    ImageButton* m_repeat;
    QSpacerItem* m_lowerSpacer8;
    ImageButton* m_volume;
    QSlider* m_volumeSlider;

    RepeatMode_t m_repeatMode;
    ShuffleMode_t m_shuffleMode;
    VolumeMode_t m_volumeMode;

  public slots:
    void onCurrentMediaChanged(const Track& track);
    void onPositionChanged(qint64 position, qint64 duration);

  private slots:
    void onBackwardClicked();
    void onPlayClicked();
    void onPauseClicked();
    void onForwardClicked();
    void onMusicSliderMoved(int position);
    void onShuffleClicked();
    void onRepeatClicked();
    void onVolumeClicked();
    void onVolumeSliderMoved(int position);

  signals:
    void backwardClicked();
    void playClicked();
    void pauseClicked();
    void forwardClicked();
    void musicSliderMoved(int position, int minimum, int maximum);
    void shuffleClicked(AudioControls::ShuffleMode_t shuffleMode);
    void repeatClicked(AudioControls::RepeatMode_t repeatMode);
    void volumeClicked(AudioControls::VolumeMode_t volumeMode);
    void volumeSliderMoved(int position);
};

#endif // AUDIOCONTROLS_H
