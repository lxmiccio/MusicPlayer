#ifndef SOUNDTOUCHMANAGER_H
#define SOUNDTOUCHMANAGER_H

#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>
#include <QVector>

#include "LameWrapper.h"
#include "SoundTouchWrapper.h"
#include "TagLibWrapper.h"
#include "Track.h"

struct ChangeTempoRequest
{
        QFuture<Track*> future;
        QFutureWatcher<Track*>* futureWatcher;

        QVector<QPair<Track*, qint16>> trackPairs;
};

class SoundTouchManager : public QObject
{
        Q_OBJECT

    public:
        SoundTouchManager();
        ~SoundTouchManager();

        void changeTempo(const QVector<Track*>& tracks, qint16 tempo);

    signals:
        void finished();

    private slots:
        void onResultReadyAt(int index);

    private:
        static Track* changeTrackTempo(QPair<Track*, qint16> trackPair);

        QVector<ChangeTempoRequest> m_changeTempoRequests;
};

#endif // SOUNDTOUCHMANAGER_H
