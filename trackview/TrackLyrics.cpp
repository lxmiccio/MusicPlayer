#include "TrackLyrics.h"

#include <QScrollBar>

TrackLyrics::TrackLyrics(QWidget* parent) : QWidget(parent)
{
    m_lyrics = new QLabel();
    m_lyrics->setStyleSheet(QString("color: white;"));

    m_scrollArea = new ScrollArea();
    m_scrollArea->verticalScrollBar()->hide();
    m_scrollArea->setWidget(m_lyrics);

    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_scrollArea);

    setLayout(m_layout);
}

void TrackLyrics::onTrackStarted(const Track& track)
{
    c_track = &track;

    m_lyrics->setText(c_track->lyrics());
    m_scrollArea->verticalScrollBar()->setSliderPosition(0);
}
