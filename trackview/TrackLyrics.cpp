#include "TrackLyrics.h"

#include <QScrollBar>

#include "AudioEngine.h"
#include "GuiUtils.h"
#include "TrackAlbum.h"

TrackLyrics::TrackLyrics(QWidget* parent) : QWidget(parent)
{
    m_lyrics = new QLabel();
    m_lyrics->setStyleSheet(QString("color: white;"));
    m_lyrics->setWordWrap(true);

    m_scrollableArea = new ScrollableArea();
    m_scrollableArea->verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);
    m_scrollableArea->setWidget(m_lyrics);

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_scrollableArea);

    setFixedWidth(TrackAlbum::WIDGET_HEIGHT);
    setFixedWidth(TrackAlbum::WIDGET_WIDTH);
    setLayout(m_layout);

    QObject::connect(AudioEngine::instance(), SIGNAL(trackStarted(const Track&)), this, SLOT(onTrackStarted(const Track&)));
}

void TrackLyrics::onTrackStarted(const Track& track)
{
    c_track = &track;

    m_lyrics->setText(c_track->lyrics());
    m_scrollableArea->verticalScrollBar()->setSliderPosition(0);
}
