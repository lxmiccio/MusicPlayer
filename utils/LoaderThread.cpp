#include "LoaderThread.h"

void LoaderThread::loadFile(const QFileInfo& file)
{
    Track* track;

    if(file.suffix() == "flac")
    {
        track = TagUtils::readFlac(file);
    }
    else if(file.suffix() == "mp3")
    {
        track = TagUtils::readMp3(file);
    }

    emit fileLoaded(*track);
}
