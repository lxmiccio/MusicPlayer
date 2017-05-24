#include "LameWrapper.h"

#include <QFile>

#include "get_audio.h"

LameWrapper::LameWrapper(QObject* parent) : QObject(parent)
{
}

LameWrapper::~LameWrapper()
{
    close_infile();
    lame_close(m_lame);
}

bool LameWrapper::init(const QString& inputPath, const QString& outputPath)
{
    bool ok = true;

    m_lame = lame_init();

    m_inputPath = inputPath;
    m_outputPath = outputPath;

    if(init_infile(m_lame, m_inputPath.toUtf8().data()) < 0)
    {
        ok = false;
    }

    if((m_output = init_outfile(m_outputPath.toUtf8().data(), lame_get_decode_only(m_lame))) == NULL)
    {
        ok = false;
    }

    lame_init_params(m_lame);

    return ok;
}

void LameWrapper::decode(bool asynchronous)
{
    if(!asynchronous)
    {
        process();
    }
    else
    {
        //Move to QThread and emit signal when processing is completed
    }
}

void LameWrapper::process()
{
    short int buffer[2][1152];
    double wavFileSize = 0;
    int i;
    int samplesRead;
    int channels = lame_get_num_channels(m_lame);

    /* Since size is actually unknown, write maximum 32 bit signed value */
    WriteWaveHeader(m_output, 0x7FFFFFFF, lame_get_in_samplerate(m_lame), channels, 16);

    do
    {
        /* Read samples in buffer */
        samplesRead = get_audio16(m_lame, buffer);

        if (samplesRead > 0)
        {
            wavFileSize += samplesRead;
            put_audio16(m_output, buffer, samplesRead, channels);
        }
    }
    while (samplesRead > 0);

    i = (16 / 8) * channels;

    if(wavFileSize <= 0)
    {
        wavFileSize = 0;
    }
    else if(wavFileSize > 0xFFFFFFD0 / i)
    {
        wavFileSize = 0xFFFFFFD0;
    }
    else
    {
        wavFileSize *= i;
    }

    /* if output file is still seekable, rewind and update size */
    if(fseek(m_output, 0l, SEEK_SET) == 0)
    {
        WriteWaveHeader(m_output, (int) wavFileSize, lame_get_in_samplerate(m_lame), channels, 16);
    }

    fclose(m_output);
}
