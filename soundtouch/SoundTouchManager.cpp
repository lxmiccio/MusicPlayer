#include "SoundTouchManager.h"
#include "MusicLibrary.h"

SoundTouchManager::SoundTouchManager()
{

}

SoundTouchManager::~SoundTouchManager()
{

}

void SoundTouchManager::changeTempo(const QVector<Track*>& tracks, qint16 tempo)
{
    ChangeTempoRequest request;

    foreach(Track* i_track, tracks)
    {
        request.trackPairs.push_back(qMakePair(i_track, tempo));
    }

    request.futureWatcher = new QFutureWatcher<Track*>();

    QObject::connect(request.futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(onResultReadyAt(int)));
    QObject::connect(request.futureWatcher, SIGNAL(finished()), this, SIGNAL(finished()));

    request.future = QtConcurrent::mapped(request.trackPairs.begin(), request.trackPairs.end(), &SoundTouchManager::changeTrackTempo);
    request.futureWatcher->setFuture(request.future);

    m_changeTempoRequests.push_back(request);
}

void SoundTouchManager::onResultReadyAt(int index)
{
    Q_UNUSED(index);

    QFutureWatcher<Track*>* sender = static_cast<QFutureWatcher<Track*>*>(QObject::sender());

    for(quint8 i = 0; i < m_changeTempoRequests.size(); ++i)
    {
        if(m_changeTempoRequests.at(i).futureWatcher == sender)
        {
            delete m_changeTempoRequests.takeAt(i).futureWatcher;
        }
    }
}

Track* SoundTouchManager::changeTrackTempo(QPair<Track*, qint16> trackPair)
{
    Track* track = trackPair.first;
    qint16 tempo = trackPair.second;

    QString lameDecodeInput = track->path();
    QString lameDecodeOutput = QString(track->path()).replace(".mp3", ".wav");
    {
        LameWrapper decoder(lameDecodeInput, lameDecodeOutput);
        decoder.decode();
    }

    QString soundTouchOutput = QString(lameDecodeOutput).replace(".wav", "_" + QString(QString::number(tempo) + ".wav"));
    {
        SoundTouchWrapper soundTouch(lameDecodeOutput, soundTouchOutput);
        soundTouch.setTempo(tempo);
        soundTouch.process();
    }

    QString lameEncodeOutput = QString(soundTouchOutput).replace(".wav", ".mp3");
    {
        LameWrapper encoder(soundTouchOutput, lameEncodeOutput);
        encoder.encode();
    }

    QFile(lameDecodeOutput).remove();
    QFile(soundTouchOutput).remove();

    TagLibWrapper::setMp3Tags(lameEncodeOutput, track->mp3Tags());
    TagLibWrapper::setMp3Cover(lameEncodeOutput, track->album()->cover());
    TagLibWrapper::readMp3Cover(QFileInfo(lameEncodeOutput));

//    QVector<QFileInfo> files;
//    files.append(QFileInfo(lameEncodeOutput));
//    MusicLibrary::instance()->onTracksToLoad(files);

    return track;
}
