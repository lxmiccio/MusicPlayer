#include "PlayingLyrics.h"

#include "AudioEngine.h"
#include "PlayingAlbum.h"

PlayingLyrics::PlayingLyrics(QWidget* parent) : ScrollableArea(parent)
{
    m_lyrics = new QLabel();
    m_lyrics->setStyleSheet(QString("color: white;"));
    m_lyrics->setWordWrap(true);

    setMinimumWidth(PlayingAlbum::WIDGET_WIDTH);
    setWidget(m_lyrics);

    QObject::connect(AudioEngine::instance(), SIGNAL(trackStarted(const Track*)), this, SLOT(onTrackStarted(const Track*)));
}

void PlayingLyrics::onTrackStarted(const Track* track)
{
    if(track)
    {
        if(track != c_track)
        {
            c_track = track;
            m_lyrics->setText(const_cast<Track*>(c_track)->lyrics());
        }

        verticalScrollBar()->setSliderPosition(0);
    }
}
