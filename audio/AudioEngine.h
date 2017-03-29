#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>
#include <QPointer>

#include "AudioControls.h"
#include "Playlist.h"
#include "Settings.h"
#include "Track.h"

class AudioEngine : public QObject
{
        Q_OBJECT

    public:
        static AudioEngine* instance();
        void close();

        Playlist* playlist();

    protected:
        AudioEngine();
        ~AudioEngine();

    public slots:
        void onPlaylistSelected(Playlist* playlist);
        void onTrackSelected(const Track& track);
        void onTrackSelected(Track* track);

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
        static QPointer<AudioEngine> m_instance;

        Playlist* m_playlist;
        QMediaPlayer* m_mediaPlayer;
        QMediaPlaylist* m_mediaPlaylist;
};

#endif // AUDIOENGINE_H
