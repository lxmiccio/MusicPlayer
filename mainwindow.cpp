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

#include "loadplaylistwindow.h"
#include "saveplaylistwindow.h"

#include "ImageUtils.h"

#include "TrackItem.h"

#include "ScrollArea.h"
#include "Cover.h"

#include "ImageUtils.h"

MainWindow::MainWindow(const StackedWidget* stackedWidget, QWidget* parent) : BackgroundWidget(parent)
{
    QImage backgroud(":/images/tove-lo.jpg");
    BackgroundWidget::setBackgroundImage(QPixmap::fromImage(ImageUtils::blur(backgroud, backgroud.rect(), 100, false, true)));

    c_stackedWidget = stackedWidget;

    m_scrollArea = new ScrollArea();
    m_albumView = new AlbumView();
    m_scrollArea->setWidget(m_albumView);
    QObject::connect(m_scrollArea, SIGNAL(resized(QResizeEvent*)), m_albumView, SLOT(onScrollAreaResized(QResizeEvent*)));
    QObject::connect(m_scrollArea, SIGNAL(fileDropped(const QFileInfo&)), this, SLOT(onFileDropped(const QFileInfo&)));
    QObject::connect(this, SIGNAL(trackAdded(const Track&)), m_albumView, SLOT(onTrackAdded(const Track&)));
    QObject::connect(m_albumView, SIGNAL(coverClicked(const Album&)), this, SLOT(onCoverClicked(const Album&)));

    m_trackView = new TrackView(this);
    QObject::connect(m_trackView, SIGNAL(doubleClicked(const Track&)), this, SLOT(itemDoubleClicked(const Track&)));
    QObject::connect(m_trackView, SIGNAL(coverClicked()), this, SLOT(coverClicked()));

    m_audioEngine = new AudioEngine(this);
    QObject::connect(this, SIGNAL(trackClicked(const Track&)), m_audioEngine, SLOT(onTrackSelected(const Track&)));

    m_leftPanel = new LeftPanel();

    m_horLayout = new QHBoxLayout();
    m_horLayout->setMargin(0);
    m_horLayout->setSpacing(0);
    //m_horLayout->addWidget(m_leftPanel);
    m_horLayout->addWidget(m_scrollArea);
    m_horLayout->addWidget(m_trackView);

    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_trackView->hide();
    m_layout->addLayout(m_horLayout);
    m_layout->addWidget(m_audioEngine->audioControls());
    setLayout(m_layout);

    m_musicLibrary = new MusicLibrary();

    m_musicPlayer = new MusicPlayer();
}

void MainWindow::itemDoubleClicked(const Track& track)
{
    emit trackClicked(track);

    //    Playlist* p = new Playlist("temp");
    //    p->addTrack(track);
    //    this->m_musicPlayer->setPlaylist(*p);
}

void MainWindow::coverClicked()
{
    m_scrollArea->show();
    m_trackView->hide();
}

void MainWindow::onCoverClicked(const Album& album)
{
    m_trackView->show();
    m_trackView->onAlbumSelected(album);
    m_scrollArea->hide();

    foreach(Track* i_track, album.tracks())
        qDebug() << i_track->title();
}

void MainWindow::onFileDropped(const QFileInfo& fileInfo)
{
    QVariantMap tags = TagUtils::readTags(fileInfo).toMap();
    tags["cover"] = TagUtils::readCover(fileInfo);
    tags["lyrics"] = TagUtils::readLyrics(fileInfo);

    Track* track = this->m_musicLibrary->addTrack(tags);

    if(track)
    {
        TrackItem* trackItem = new TrackItem(track);
        //this->model->appendRow(ti->getItems());

        //this->m_musicLibrary->debug();
        //this->items.push_back(ti);

        emit trackAdded(*track);
    }
}

#if 0
void MainWindow::musicSliderMoved(int value)
{
    this->musicPlayer->getMediaPlayer()->setPosition((this->musicPlayer->getMediaPlayer()->duration() * value) / (this->musicSlider->maximum() - this->musicSlider->minimum()));
}

void MainWindow::musicSliderPressed()
{
    QObject::disconnect(this->musicPlayer->getMediaPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(mediaPlayerPositionChanged(qint64)));
}

void MainWindow::musicSliderReleased()
{
    QObject::connect(this->musicPlayer->getMediaPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(mediaPlayerPositionChanged(qint64)));
}

void MainWindow::volumeSliderMoved(int value)
{
    this->musicPlayer->getMediaPlayer()->setVolume(value);
}

void MainWindow::volumeValueChanged(int value)
{
    this->musicPlayer->getMediaPlayer()->setVolume(value);
}
#endif
