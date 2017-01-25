#include "TrackLoader.h"

#include <QDebug>
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
    QObject::connect(loaderThread, SIGNAL(onTracksLoaded()), this, SLOT(handleResults()));

    thread->start();
}
