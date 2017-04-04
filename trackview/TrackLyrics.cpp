#include "TrackLyrics.h"

TrackLyrics::TrackLyrics(QWidget* parent) : ScrollableArea(parent)
{
    m_lyrics = new QLabel();
    m_lyrics->setStyleSheet(QString("color: white;"));
    m_lyrics->setWordWrap(true);

    setMinimumWidth(TrackAlbum::WIDGET_WIDTH);
    setWidget(m_lyrics);
    verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);

    QObject::connect(AudioEngine::instance(), SIGNAL(trackStarted(const Track*)), this, SLOT(onTrackStarted(const Track*)));
}

void TrackLyrics::onTrackStarted(const Track* track)
{
    if(track)
    {
        if(track != c_track)
        {
            c_track = track;
            m_lyrics->setText(c_track->lyrics());
        }

        verticalScrollBar()->setSliderPosition(0);
    }
}
