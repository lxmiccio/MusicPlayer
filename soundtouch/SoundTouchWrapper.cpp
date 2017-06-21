#include "SoundTouchWrapper.h"

SoundTouchWrapper::SoundTouchWrapper(const QString& inputPath, const QString& outputPath, QObject* parent) : QObject(parent)
{
    m_inputPath = inputPath;
    m_outputPath = outputPath;

    m_inFile = new WavInFile(inputPath.toUtf8().data());

    m_bits = m_inFile->getNumBits();
    m_channels = m_inFile->getNumChannels();
    m_sampleRate = m_inFile->getSampleRate();

    m_outFile = new WavOutFile(outputPath.toUtf8().data(), m_sampleRate, m_bits, m_channels);

    m_pitch = 0;
    m_rate = 0;
    m_tempo = 0;

    m_soundTouch.setChannels(m_channels);
    m_soundTouch.setSampleRate(m_sampleRate);

    m_soundTouch.setPitchSemiTones(m_pitch);
    m_soundTouch.setRateChange(m_rate);
    m_soundTouch.setTempoChange(m_tempo);

    m_soundTouch.setSetting(SETTING_USE_AA_FILTER, true);
    m_soundTouch.setSetting(SETTING_USE_QUICKSEEK, false);
}

SoundTouchWrapper::~SoundTouchWrapper()
{
    delete m_inFile;
    delete m_outFile;
}

void SoundTouchWrapper::setPitch(qint8 pitch)
{
    m_pitch = pitch;
    m_soundTouch.setPitchSemiTones(m_pitch);
}

void SoundTouchWrapper::setRate(qint8 rate)
{
    m_rate = rate;
    m_soundTouch.setRateChange(m_rate);
}

void SoundTouchWrapper::setTempo(qint8 tempo)
{
    m_tempo = tempo;
    m_soundTouch.setTempoChange(m_tempo);
}

void SoundTouchWrapper::process()
{
    SAMPLETYPE sampleBuffer[BUFF_SIZE];

    int samples;
    int maxSamples = BUFF_SIZE / m_channels;

    while(!m_inFile->eof())
    {
        int samplesRead = m_inFile->read(sampleBuffer, BUFF_SIZE);
        samples = samplesRead / m_channels;

        m_soundTouch.putSamples(sampleBuffer, samples);

        do
        {
            samples = m_soundTouch.receiveSamples(sampleBuffer, maxSamples);
            m_outFile->write(sampleBuffer, samples * m_channels);
        }
        while(samples != 0);
    }

    m_soundTouch.flush();

    do
    {
        samples = m_soundTouch.receiveSamples(sampleBuffer, maxSamples);
        m_outFile->write(sampleBuffer, samples * m_channels);
    }
    while(samples != 0);

    emit processed(m_outputPath);
}
