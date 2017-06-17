#include "TrackLoaderThread.h"

static Mp3Tags* loadTrack(QFileInfo &file)
{
    Mp3Tags* tags = new Mp3Tags();

    if(file.suffix() == "flac")
    {
        TagLibWrapper::readFlacTags(file.canonicalFilePath(), tags);
    }
    else if(file.suffix() == "mp3")
    {
        TagLibWrapper::readMp3Tags(file.canonicalFilePath(), tags);
        TagLibWrapper::readMp3Lyrics(file.canonicalFilePath(), tags);
    }

    return tags;
}

TrackLoaderThread::~TrackLoaderThread()
{
    m_future.cancel();
    m_futureWatcher.cancel();
    m_future.waitForFinished();
    m_futureWatcher.waitForFinished();
}

void TrackLoaderThread::readTags(const QVector<QFileInfo>& files)
{
    for(QVector<QFileInfo>::ConstIterator i_file = files.begin(); i_file < files.end(); ++i_file)
    {
        if(i_file->suffix() == "flac" || i_file->suffix() == "mp3")
        {
            m_files.push_back(*i_file);
        }
    }

    QObject::connect(&m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(onTagsRead(int)));
    QObject::connect(&m_futureWatcher, SIGNAL(finished()), this, SIGNAL(finished()));

    m_future = QtConcurrent::mapped(m_files.begin(), m_files.end(), loadTrack);
    m_futureWatcher.setFuture(m_future);
}

void TrackLoaderThread::onTagsRead(int index)
{
    emit tagsRead(m_future.resultAt(index));
}
