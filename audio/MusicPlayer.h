#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>

#include "AudioControls.h"
#include "playlist.h"
#include "Track.h"

class MusicPlayer : public QObject
{
    Q_OBJECT

    public:
        MusicPlayer(QObject* parent = 0);

        QMediaPlayer* mediaPlayer() const;
        QMediaPlaylist* mediaPlaylist() const;

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

    signals:
        void trackStarted(const Track& track);
        void trackFinished();
        void positionChanged(qint64 position, qint64 duration);

    private slots:
        void onCurrentIndexChanged(int index);
        void onPositionChanged(qint64 position);

    private:
        Playlist* m_playlist;

        QMediaPlayer* m_mediaPlayer;
        QMediaPlaylist* m_mediaPlaylist;
};

#endif // MUSICPLAYER_H
