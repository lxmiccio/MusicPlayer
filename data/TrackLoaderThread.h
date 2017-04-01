#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <QtConcurrent>
#include <QFileInfo>
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>

#include "TagUtils.h"
#include "Track.h"

class TrackLoaderThread : public QObject
{
        Q_OBJECT

    public:
        ~TrackLoaderThread();

    public slots:
        void readTags(const QVector<QFileInfo>& files);

    private slots:
        void onTagsRead(int index);

    signals:
        void tagsRead(QVariantMap* tags);
        void finished();

    private:
        QVector<QFileInfo> m_files;
        QFuture<QVariantMap*> m_future;
        QFutureWatcher<QVariantMap*> m_futureWatcher;
};

#endif // LOADERTHREAD_H
