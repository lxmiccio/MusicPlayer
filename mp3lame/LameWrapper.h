#ifndef LAMEWRAPPER_H
#define LAMEWRAPPER_H

#ifdef DEBUG
#include <QDebug>
#endif

#include <QMutex>
#include <QMutexLocker>
#include <QObject>

#include "get_audio.h"

class LameWrapper : public QObject
{
        Q_OBJECT

    public:
        LameWrapper(const QString& inputPath, const QString& outputPath, QObject* parent = 0);
        ~LameWrapper();

        bool decode();
        bool encode();

#ifdef DEBUG
        static void debugHookHandler(const char* message, void* const object)
        {
            LameWrapper* lameWrapper =  static_cast<LameWrapper*>(object);
            qDebug() << lameWrapper << message;
        }
#endif

    signals:
        void decoded(QByteArray data);

    private:
        bool writeId3v1Tags();
        size_t writeId3v2Tags();
        bool writeXingFrame(size_t id3v2TagSize);

        void process();

        AudioData m_inputAudioData;
        DecoderConfig m_decoderConfig;
        RawPCMConfig m_rawPcmConfig;
        ReaderConfig m_readerConfig;
        WriterConfig m_writerConfig;

        lame_t m_lame;
        QString m_inputPath;
        QString m_outputPath;

        FILE* m_output;

        static QMutex MUTEX;
};

#endif // LAMEWRAPPER_H
