#include "PlayingLyrics.h"

#include "AudioEngine.h"
#include "PlayingAlbum.h"

PlayingLyrics::PlayingLyrics(QWidget* parent) : ScrollableArea(parent)
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
        if(track != c_track)
        {
            c_track = track;
            QObject::connect(c_track, SIGNAL(trackUpdated(Track*, quint8)), this, SLOT(onTrackUpdated(Track*, quint8)));

            m_lyrics->setText(c_track->lyrics());
        }

        verticalScrollBar()->setSliderPosition(0);
    }
}

void PlayingLyrics::onTrackUpdated(Track* track, quint8 fields)
{
    if(track && track == c_track && (fields & Track::LYRICS))
    {
        m_lyrics->setText(track->lyrics());
    }
}
