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
#include "ScrollArea.h"
#include "TrackItem.h"

MainWindow::MainWindow(const StackedWidget* stackedWidget, QWidget* parent) : BackgroundWidget(parent)
{
    QImage backgroud(":/images/tove-lo.jpg");
    BackgroundWidget::setBackgroundImage(QPixmap::fromImage(ImageUtils::blur(backgroud, backgroud.rect(), 15, false, true)));

    c_stackedWidget = stackedWidget;

    m_scrollArea = new ScrollArea();
    m_albumView = new AlbumView();
    m_scrollArea->setWidget(m_albumView);
    QObject::connect(m_scrollArea, SIGNAL(resized(QResizeEvent*)), m_albumView, SLOT(onScrollAreaResized(QResizeEvent*)));
    QObject::connect(m_scrollArea, SIGNAL(trackLoaded(Track)), this, SLOT(onTrackLoaded(const Track&)));
    QObject::connect(m_scrollArea, SIGNAL(mp3Dropped(const QFileInfo&)), this, SLOT(onMp3Dropped(const QFileInfo&)));
    QObject::connect(this, SIGNAL(trackAdded(const Track&)), m_albumView, SLOT(onTrackAdded(const Track&)));
    QObject::connect(m_albumView, SIGNAL(coverClicked(const Album&)), this, SLOT(onCoverClicked(const Album&)));

    m_trackView = new TrackView(this);
    QObject::connect(m_trackView, SIGNAL(doubleClicked(const Track&)), this, SLOT(onItemDoubleClicked(const Track&)));
    QObject::connect(m_trackView, SIGNAL(coverClicked()), this, SLOT(coverClicked()));

    QObject::connect(this, SIGNAL(trackStarted(const Track&)), m_trackView, SLOT(onTrackStarted(const Track&)));


    m_audioManager = new AudioManager(this);
    QObject::connect(this, SIGNAL(trackClicked(const Track&)), m_audioManager, SLOT(onTrackSelected(const Track&)));
    QObject::connect(m_audioManager, SIGNAL(trackStarted(const Track&)), this, SLOT(onTrackStarted(const Track&)));

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
    m_layout->addWidget(m_audioManager);
    setLayout(m_layout);

    m_musicLibrary = MusicLibrary::instance();
}

void MainWindow::onItemDoubleClicked(const Track& track)
{
    emit trackClicked(track);
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
}

void MainWindow::onTrackSelected(const Track& track)
{
    //emit trackSelected(track);
}

void MainWindow::onTrackStarted(const Track& track)
{
    emit trackStarted(track);
}

void MainWindow::onTrackLoaded(const Track& fileInfo)
{
    qDebug() << "sdfsfsdf";
    {
        emit trackAdded(fileInfo);
    }
}

void MainWindow::onMp3Dropped(const QFileInfo& fileInfo)
{
    QVariantMap tags = TagUtils::readMp3Tags(fileInfo).toMap();
    tags["cover"] = TagUtils::readMp3Cover(fileInfo);
    tags["lyrics"] = TagUtils::readMp3Lyrics(fileInfo);

    Track* track = this->m_musicLibrary->addTrack(tags);

    if(track)
    {
        emit trackAdded(*track);
    }
}
