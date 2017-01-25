#include "TrackLoader.h"

#include <QFileInfo>

TrackLoader::TrackLoader()
{

}

void TrackLoader::loadTracks(QList<QUrl> urls)
{
    QThread* thread = new QThread();

    LoaderThread* loaderThread = new LoaderThread();
    loaderThread->moveToThread(thread);

    m_threads.push_back(thread);
    m_trackLoaderThreads.push_back(loaderThread);

    QObject::connect(thread, SIGNAL(finished()), loaderThread, SLOT(deleteLater()));
    QObject::connect(loaderThread, SIGNAL(trackLoaded(Track*)), this, SLOT(onTrackLoaded(Track*)));
    QObject::connect(loaderThread, SIGNAL(tracksLoaded()), this, SLOT(onTracksLoaded()));

    thread->start();
    loaderThread->loadTracks(urls);
}

void TrackLoader::onTrackLoaded(Track* track)
{
    emit trackLoaded(track);
}

void TrackLoader::onTracksLoaded()
{
    LoaderThread* sender = static_cast<LoaderThread*>(QObject::sender());
    quint8 index = m_trackLoaderThreads.indexOf(sender);

    delete m_trackLoaderThreads.at(index);
    m_trackLoaderThreads.removeAt(index);
    m_threads.removeAt(index);
}
