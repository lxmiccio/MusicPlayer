#include "PlayingLyrics.h"

#include "AudioEngine.h"
#include "PlayingAlbum.h"

PlayingLyrics::PlayingLyrics(QWidget* parent) : ScrollableWidget(parent)
{
    m_lyrics = new QLabel();
    m_lyrics->setStyleSheet("color: white;");
    m_lyrics->setWordWrap(true);

    setMinimumWidth(PlayingAlbum::WIDGET_WIDTH);
    setWidget(m_lyrics);

    QObject::connect(AudioEngine::instance(), SIGNAL(trackStarted(Track*)), this, SLOT(onTrackStarted(Track*)));
}

PlayingLyrics::~PlayingLyrics()
{
    delete m_lyrics;
}

void PlayingLyrics::onTrackStarted(Track* track)
{
    if(track)
    {
        if(track != m_track)
        {
            m_track = track;
            QObject::connect(m_track, SIGNAL(trackUpdated(Track*, quint8)), this, SLOT(onTrackUpdated(Track*, quint8)));

            m_lyrics->setText(m_track->lyrics());
        }

        verticalScrollBar()->setSliderPosition(0);
    }
}

void PlayingLyrics::onTrackUpdated(Track* track, quint8 fields)
{
    if(track && track == m_track && (fields & Track::LYRICS))
    {
        m_lyrics->setText(track->lyrics());
    }
}
