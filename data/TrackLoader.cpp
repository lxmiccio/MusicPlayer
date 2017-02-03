#include "TrackLoader.h"

TrackLoader::TrackLoader()
{
}

void TrackLoader::loadTracks(const QVector<QFileInfo>& filesInfo)
{
    QThread* thread = new QThread();

    TrackLoaderThread* trackLoaderThread = new TrackLoaderThread();
    trackLoaderThread->moveToThread(thread);

    m_threads.push_back(thread);
    m_trackLoaderThreads.push_back(trackLoaderThread);

    QObject::connect(thread, SIGNAL(finished()), trackLoaderThread, SLOT(deleteLater()));
    QObject::connect(trackLoaderThread, SIGNAL(trackLoaded(Track*)), this, SLOT(onTrackLoaded(Track*)));
    QObject::connect(trackLoaderThread, SIGNAL(tracksLoaded()), this, SLOT(onTracksLoaded()));

    thread->start();
    trackLoaderThread->loadTracks(filesInfo);
}

void TrackLoader::onTrackLoaded(Track* track)
{
    emit trackLoaded(track);
}

void TrackLoader::onTracksLoaded()
{
    TrackLoaderThread* sender = static_cast<TrackLoaderThread*>(QObject::sender());
    qint8 index = m_trackLoaderThreads.indexOf(sender);

    delete m_trackLoaderThreads.at(index);
    m_trackLoaderThreads.removeAt(index);
    m_threads.removeAt(index);
}
