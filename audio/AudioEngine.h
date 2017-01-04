#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>

#include "AudioControls.h"
#include "MusicPlayer.h"

class AudioEngine : public QObject
{
    Q_OBJECT

public:
    AudioEngine(QObject* parent = 0);

    AudioControls* audioControls();

public slots:
    void onTrackSelected(const Track& track);

signals:
    trackSelected(const Track& track);

private:
    AudioControls* m_audioControls;
    MusicPlayer* m_musicPlayer;
};

#endif // AUDIOENGINE_H
