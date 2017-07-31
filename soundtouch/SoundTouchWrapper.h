#ifndef SOUNDTOUCHWRAPPER_H
#define SOUNDTOUCHWRAPPER_H

#include <QObject>

#include "SoundTouch.h"
#include "WavFile.h"

using namespace soundtouch;

class SoundTouchWrapper : public QObject
{
        Q_OBJECT

    public:
        SoundTouchWrapper(const QString& inputPath, const QString& outputPath = QString(), QObject* parent = 0);
        ~SoundTouchWrapper();

        void setPitch(qint8 pitch);
        void setRate(qint8 rate);
        void setTempo(qint8 tempo);

        void process();

    signals:
        void processed(QString outputFile);

    private:
        SoundTouch m_soundTouch;
        WavInFile* m_inFile;
        WavOutFile* m_outFile;

        quint64 m_bits;
        quint16 m_channels;
        quint32 m_sampleRate;

        quint8 m_pitch;
        quint8 m_rate;
        quint8 m_tempo;

        QString m_inputPath;
        QString m_outputPath;

        static const quint16 BUFF_SIZE = 1024;
};

#endif// SOUNDTOUCHWRAPPER_H
