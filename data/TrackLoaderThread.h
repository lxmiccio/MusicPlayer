#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <QtConcurrent>
#include <QFileInfo>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>

#include "TagLibWrapper.h"
#include "Track.h"

class TrackLoaderThread : public QObject
{
        Q_OBJECT

    public:
        ~TrackLoaderThread();

    public slots:
        void readTags(const QVector<QFileInfo>& files);

    signals:
        void tagsRead(Mp3Tags* tags);
        void finished();

    private slots:
        void onTagsRead(int index);

    private:
        QVector<QFileInfo> m_files;
        QFuture<Mp3Tags*> m_future;
        QFutureWatcher<Mp3Tags*> m_futureWatcher;
};

#endif // LOADERTHREAD_H
