#include "TrackLoader.h"

TrackLoader::TrackLoader()
{
}

TrackLoader::~TrackLoader()
{
    for(quint8 i = 0; i < m_threads.size() && i < m_trackLoaderThreads.size(); ++i)
    {
        delete m_trackLoaderThreads.at(i);
        m_threads.at(i)->deleteLater();
    }
}

void TrackLoader::readTags(const QVector<QFileInfo>& files)
{
    QThread* thread = new QThread();

    TrackLoaderThread* trackLoaderThread = new TrackLoaderThread();
    trackLoaderThread->moveToThread(thread);

    m_threads.push_back(thread);
    m_trackLoaderThreads.push_back(trackLoaderThread);

    QObject::connect(trackLoaderThread, SIGNAL(tagsRead(QVariantMap*)), this, SIGNAL(tagsRead(QVariantMap*)));
    QObject::connect(trackLoaderThread, SIGNAL(finished()), this, SLOT(onThreadFinished()));
    QObject::connect(trackLoaderThread, SIGNAL(finished()), trackLoaderThread, SLOT(deleteLater()));
    QObject::connect(trackLoaderThread, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
    trackLoaderThread->readTags(files);
}

void TrackLoader::onThreadFinished()
{
    TrackLoaderThread* sender = static_cast<TrackLoaderThread*>(QObject::sender());
    qint8 index = m_trackLoaderThreads.indexOf(sender);

    if(index != -1)
    {
        m_trackLoaderThreads.removeAt(index);
        m_threads.removeAt(index);
        delete sender;
    }
}
