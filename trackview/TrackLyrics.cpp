#include "TrackLyrics.h"

#include <QScrollBar>

#include "AudioEngine.h"

TrackLyrics::TrackLyrics(QWidget* parent) : QWidget(parent)
{
    m_lyrics = new QLabel();
    m_lyrics->setStyleSheet(QString("color: white;"));

    m_scrollableArea = new ScrollableArea();
    m_scrollableArea->verticalScrollBar()->hide();
    m_scrollableArea->setWidget(m_lyrics);

    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_scrollableArea);

    setLayout(m_layout);

    QObject::connect(AudioEngine::instance(), SIGNAL(trackStarted(const Track&)), this, SLOT(onTrackStarted(const Track&)));
}

void TrackLyrics::onTrackStarted(const Track& track)
{
    c_track = &track;

    m_lyrics->setText(c_track->lyrics());
    m_scrollableArea->verticalScrollBar()->setSliderPosition(0);
}
