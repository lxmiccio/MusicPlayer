#include "LameWrapper.h"

#include "sys/stat.h"

QMutex LameWrapper::MUTEX;

LameWrapper::LameWrapper(const QString& inputPath, const QString& outputPath, QObject* parent) : QObject(parent)
{
#ifdef DEBUG
    DebugHook hook;
    hook.DebugHook = &debugHookHandler;
    registerHook(hook, this);
#endif

    m_inputPath = inputPath;
    m_outputPath = outputPath;

    m_rawPcmConfig.in_bitwidth = 16;
    m_rawPcmConfig.in_signed = -1;
    m_rawPcmConfig.in_endian = ByteOrderLittleEndian;

    m_readerConfig.input_format = sf_unknown;
    m_readerConfig.input_samplerate = 0;
    m_readerConfig.swap_channel = 0;
    m_readerConfig.swapbytes = 0;

    m_writerConfig.flush_write = 0;

    m_lame = lame_init();
    lame_init_params(m_lame);

    init_infile(m_lame, &m_inputAudioData, &m_readerConfig, &m_decoderConfig, &m_rawPcmConfig, m_inputPath.toUtf8().data());
}

LameWrapper::~LameWrapper()
{
}

bool LameWrapper::decode()
{
    bool ok = true;

    m_output = init_outfile(m_outputPath.toUtf8().data(), lame_get_decode_only(m_lame));

    if(m_output)
    {
        double wavFileSize = 0;
        short channels = lame_get_num_channels(m_lame), i, samplesRead;
        short int buffer[2][1152];

        /* Since size is actually unknown, write maximum 32 bit signed value */
        WriteWaveHeader(m_output, 0x7FFFFFFF, lame_get_in_samplerate(m_lame), channels, 16);

        QMutexLocker locker(&MUTEX);
        do
        {
            /* Read samples in buffer */
            samplesRead = get_audio16(m_lame, &m_inputAudioData, &m_readerConfig, &m_decoderConfig, &m_rawPcmConfig, buffer);

            if(samplesRead > 0)
            {
                wavFileSize += samplesRead;
                put_audio16(&m_readerConfig, &m_writerConfig, &m_decoderConfig, m_output, buffer, samplesRead, channels);
            }
        }
        while(samplesRead > 0);
        locker.unlock();

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

        close_infile(&m_inputAudioData);
        fclose(m_output);
        lame_close(m_lame);
    }
    else
    {
        ok = false;
    }

    return ok;
}

bool LameWrapper::encode()
{
    bool ok = true;

    m_output = init_outfile(m_outputPath.toUtf8().data(), 0);

    if(m_output)
    {
        unsigned char buffer[LAME_MAXMP3BUFFER];
        int pcm[2][1152];
        int samplesRead;

        size_t read, written;
        size_t id3v2TagSize = writeId3v2Tags();

        do
        {
            samplesRead = get_audio(m_lame, &m_inputAudioData, &m_readerConfig, &m_decoderConfig, &m_rawPcmConfig, pcm);
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

        close_infile(&m_inputAudioData);
        fclose(m_output);
        lame_close(m_lame);
    }
    else
    {
        ok = false;
    }

    return ok;
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
        unsigned char* id3v2tag = getOldTag(m_lame, &m_inputAudioData);

        id3v2TagSize = sizeOfOldTag(m_lame, &m_inputAudioData);
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
