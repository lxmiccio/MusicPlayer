#include "mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMediaMetaData>
#include <QString>
#include <QStringList>

#include <QStandardItem>
#include <QScrollArea>
#include <QHeaderView>
#include <QList>
#include <QScrollBar>

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "Cover.h"
#include "ImageUtils.h"
#include "ScrollableArea.h"
#include "TrackItem.h"

MainWindow::MainWindow(const StackedWidget* stackedWidget, QWidget* parent) : BackgroundWidget(parent)
{
    QImage backgroud(":/images/tove-lo.jpg");
    BackgroundWidget::setBackgroundImage(QPixmap::fromImage(ImageUtils::blur(backgroud, backgroud.rect(), 15, false, true)));

    c_stackedWidget = stackedWidget;

    m_scrollableArea = new ScrollableArea();
    m_albumView = new AlbumView();
    m_scrollableArea->setWidget(m_albumView);
    QObject::connect(m_scrollableArea, SIGNAL(resized(QResizeEvent*)), m_albumView, SLOT(onScrollAreaResized(QResizeEvent*)));
    QObject::connect(m_albumView, SIGNAL(coverClicked(const Album&)), this, SLOT(onCoverClicked(const Album&)));

    m_trackView = new TrackView(this);
    QObject::connect(m_trackView, SIGNAL(doubleClicked(const Track&)), this, SLOT(onItemDoubleClicked(const Track&)));
    QObject::connect(m_trackView, SIGNAL(coverClicked()), this, SLOT(coverClicked()));

    QObject::connect(this, SIGNAL(trackStarted(const Track&)), m_trackView, SLOT(onTrackStarted(const Track&)));

    m_audioControls = new AudioControls();

    m_audioEngine = AudioEngine::instance();

    QObject::connect(m_audioControls, SIGNAL(backwardClicked()), m_audioEngine, SLOT(onBackwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(playClicked()), m_audioEngine, SLOT(onPlayClicked()));
    QObject::connect(m_audioControls, SIGNAL(pauseClicked()), m_audioEngine, SLOT(onPauseClicked()));
    QObject::connect(m_audioControls, SIGNAL(forwardClicked()), m_audioEngine, SLOT(onForwardClicked()));
    QObject::connect(m_audioControls, SIGNAL(trackValueChanged(int)), m_audioEngine, SLOT(onTrackValueChanged(int)));
    QObject::connect(m_audioControls, SIGNAL(shuffleClicked(AudioControls::ShuffleMode_t)), m_audioEngine, SLOT(onShuffleClicked(AudioControls::ShuffleMode_t)));
    QObject::connect(m_audioControls, SIGNAL(repeatClicked(AudioControls::RepeatMode_t)), m_audioEngine, SLOT(onRepeatClicked(AudioControls::RepeatMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeClicked(AudioControls::VolumeMode_t)), m_audioEngine, SLOT(onVolumeClicked(AudioControls::VolumeMode_t)));
    QObject::connect(m_audioControls, SIGNAL(volumeValueChanged(int)), m_audioEngine, SLOT(onVolumeValueChanged(int)));

    QObject::connect(m_audioEngine, SIGNAL(trackStarted(const Track&)), m_audioControls, SLOT(onTrackStarted(const Track&)));
    QObject::connect(m_audioEngine, SIGNAL(positionChanged(qint64)), m_audioControls, SLOT(onPositionChanged(qint64)));
    QObject::connect(m_audioEngine, SIGNAL(trackFinished()), m_audioControls, SLOT(onTrackFinished()));


    QObject::connect(m_audioEngine, SIGNAL(trackStarted(const Track&)), this, SLOT(onTrackStarted(const Track&)));
    QObject::connect(this, SIGNAL(trackClicked(const Track&)), m_audioEngine, SLOT(onTrackSelected(const Track&)));



#if 0



#endif


    m_horLayout = new QHBoxLayout();
    m_horLayout->setMargin(0);
    m_horLayout->setSpacing(0);
    m_horLayout->addWidget(m_scrollableArea);
    m_horLayout->addWidget(m_trackView);

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_trackView->hide();
    m_layout->addLayout(m_horLayout);
    m_layout->addWidget(m_audioControls);
    setLayout(m_layout);

    m_musicLibrary = MusicLibrary::instance();
    m_trackLoader = new TrackLoader();
    QObject::connect(m_scrollableArea, SIGNAL(filesDropped(QVector<QFileInfo>)), m_trackLoader, SLOT(loadTracks(QVector<QFileInfo>)));
}

void MainWindow::onItemDoubleClicked(const Track& track)
{
    emit trackClicked(track);
}

void MainWindow::coverClicked()
{
    m_scrollableArea->show();
    m_trackView->hide();
}

void MainWindow::onCoverClicked(const Album& album)
{
    m_trackView->show();
    m_trackView->onAlbumSelected(album);
    m_scrollableArea->hide();
}

void MainWindow::onTrackStarted(const Track& track)
{
    emit trackStarted(track);
}
