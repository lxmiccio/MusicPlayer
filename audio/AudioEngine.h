#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>

#include "AudioControls.h"
#include "playlist.h"
#include "Track.h"

class AudioEngine : public QObject
{
        Q_OBJECT

    public:
        AudioEngine(QObject* parent = 0);

    public slots:
        void onTrackSelected(const Track& track);

        void onBackwardClicked();
        void onPlayClicked();
        void onPauseClicked();
        void onForwardClicked();
        void onTrackValueChanged(int value);
        void onShuffleClicked(AudioControls::ShuffleMode_t shuffleMode);
        void onRepeatClicked(AudioControls::RepeatMode_t repeatMode);
        void onVolumeClicked(AudioControls::VolumeMode_t volumeMode);
        void onVolumeValueChanged(int value);

    private slots:
        void onCurrentIndexChanged(int index);
        void onPositionChanged(qint64 position);
        void onTrackStarted();

    signals:
        void positionChanged(qint64 position);
        void trackStarted(const Track& track);
        void trackFinished();

    private:
        Playlist* m_playlist;
        QMediaPlayer* m_mediaPlayer;
        QMediaPlaylist* m_mediaPlaylist;
};

#endif // AUDIOENGINE_H
