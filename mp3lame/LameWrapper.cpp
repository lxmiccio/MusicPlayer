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

bool LameWrapper::init(bool encode, const QString& inputPath, const QString& outputPath)
{
    bool ok = true;

    m_lame = lame_init();

    m_inputPath = inputPath;
    m_outputPath = outputPath;

    if(init_infile(m_lame, m_inputPath.toUtf8().data()) < 0)
    {
        ok = false;
    }

    if(encode)
    {
        if((m_output = init_outfile(m_outputPath.toUtf8().data(), 0)) == NULL)
        {
            ok = false;
        }
    }
    else
    {
        if((m_output = init_outfile(m_outputPath.toUtf8().data(), lame_get_decode_only(m_lame))) == NULL)
        {
            ok = false;
        }
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

void LameWrapper::encode(bool asynchronous)
{
    unsigned char buffer[LAME_MAXMP3BUFFER];
    int pcm[2][1152];
    int samplesRead;

    size_t read, written;
    size_t id3v2TagSize = writeId3v2Tags();

    do
    {
        samplesRead = get_audio(m_lame, pcm);
        if(samplesRead > 0)
        {
            read = lame_encode_buffer_int(m_lame, pcm[0], pcm[1], samplesRead, buffer, sizeof(buffer));
            written = fwrite(buffer, 1, read, m_output);

            if(read != written)
            {
                // Error
            }
        }
    }
    while(samplesRead > 0);

    read = lame_encode_flush(m_lame, buffer, sizeof(buffer));
    written = fwrite(buffer, 1, read, m_output);

    if(read != written)
    {
        // Error
    }

    writeId3v1Tags();
    writeXingFrame(id3v2TagSize);

    fclose(m_output);
    close_infile();
}

bool LameWrapper::writeId3v1Tags()
{
    unsigned char buffer[128];

    size_t id3v1TagSize = lame_get_id3v1_tag(m_lame, buffer, sizeof(buffer));
    if(id3v1TagSize > 0 || id3v1TagSize <= sizeof(buffer))
    {
        size_t written = fwrite(buffer, 1, id3v1TagSize, m_output);
        if(written == id3v1TagSize)
        {
            return true;
        }
    }

    return false;
}

size_t LameWrapper::writeId3v2Tags()
{
    size_t id3v2TagSize = lame_get_id3v2_tag(m_lame, 0, 0);

    if(id3v2TagSize > 0)
    {
        unsigned char* id3v2tag = static_cast<unsigned char*>(malloc(id3v2TagSize));
        if(id3v2tag)
        {
            size_t read = lame_get_id3v2_tag(m_lame, id3v2tag, id3v2TagSize);
            size_t written = fwrite(id3v2tag, 1, read, m_output);

            free(id3v2tag);

            if(written == read)
            {
                return true;
            }
        }
    }
    else
    {
        unsigned char* id3v2tag = getOldTag(m_lame);

        id3v2TagSize = sizeOfOldTag(m_lame);
        if(id3v2TagSize > 0)
        {
            size_t written = fwrite(id3v2tag, 1, id3v2TagSize, m_output);
            if(written == id3v2TagSize)
            {
                return true;
            }
        }
    }

    return id3v2TagSize;
}

bool LameWrapper::writeXingFrame(size_t id3v2TagSize)
{
    unsigned char buffer[LAME_MAXMP3BUFFER];

    size_t xingFrameSize = lame_get_lametag_frame(m_lame, buffer, sizeof(buffer));
    if(xingFrameSize > 0 && xingFrameSize <= sizeof(buffer))
    {
        if(!fseek(m_output, id3v2TagSize, SEEK_SET))
        {
            size_t written = fwrite(buffer, 1, xingFrameSize, m_output);
            if(written == xingFrameSize)
            {
                return true;
            }
        }
    }

    return false;
}
