#ifndef LAMEWRAPPER_H
#define LAMEWRAPPER_H

#include <QBuffer>
#include <QObject>

#include "lame.h"

class LameWrapper : public QObject
{
        Q_OBJECT

    public:
        LameWrapper(QObject* parent = 0);
        ~LameWrapper();

        bool init(bool encode, const QString& input, const QString& outputPath = QString());
        void decode(bool asynchronous = true);
        void encode(bool asynchronous = true);

    signals:
        void decoded(QByteArray data);

    private:
        bool writeId3v1Tags();
        size_t writeId3v2Tags();
        bool writeXingFrame(size_t id3v2TagSize);

        void process();

        lame_t m_lame;
        QString m_inputPath;
        QString m_outputPath;

        FILE* m_output;
        QByteArray m_outputBuffer;
};

#endif // LAMEWRAPPER_H