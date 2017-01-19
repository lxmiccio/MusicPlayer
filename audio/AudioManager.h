#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QVBoxLayout>
#include <QWidget>

#include "AudioControls.h"
#include "AudioEngine.h"

class AudioManager : public QWidget
{
        Q_OBJECT

    public:
        AudioManager(QWidget* parent = 0);

    public slots:
        void onTrackSelected(const Track& track);
        void onTrackStarted(const Track& track);

    signals:
        trackSelected(const Track& track);
        trackStarted(const Track& track);

    private:
        AudioEngine* m_audioEngine;

        QVBoxLayout* m_layout;
        AudioControls* m_audioControls;
};

#endif // AUDIOMANAGER_H
