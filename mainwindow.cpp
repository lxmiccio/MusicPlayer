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

    m_audioControls = new AudioControls(this);
    m_audioControls->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //QObject::connect(m_audioControls, SIGNAL(backwardClicked()), this, SLOT(onBackwardClicked()));
    //QObject::connect(m_audioControls, SIGNAL(playClicked()), this, SLOT(onPlayClicked()));
    //QObject::connect(m_audioControls, SIGNAL(pauseClicked()), this, SLOT(onPauseClicked()));
    //QObject::connect(m_audioControls, SIGNAL(forwardClicked()), this, SLOT(onForwardClicked()));
    //QObject::connect(m_audioControls, SIGNAL(musicSliderMoved(int, int, int)), this, SLOT(onMusicSliderMoved(int, int, int)));
    //QObject::connect(m_audioControls, SIGNAL(shuffleClicked(AudioControls::ShuffleMode_t)), this, SLOT(onShuffleClicked(AudioControls::ShuffleMode_t)));
    //QObject::connect(m_audioControls, SIGNAL(repeatClicked(AudioControls::RepeatMode_t)), this, SLOT(onRepeatClicked(AudioControls::RepeatMode_t)));
    //QObject::connect(m_audioControls, SIGNAL(volumeClicked(AudioControls::VolumeMode_t)), this, SLOT(onVolumeClicked(AudioControls::VolumeMode_t)));
    //QObject::connect(this, SIGNAL(currentMediaChanged(const Track&)), m_audioControls, SLOT(onCurrentMediaChanged(const Track&)));
    //QObject::connect(this, SIGNAL(positionChanged(qint64, qint64)), m_audioControls, SLOT(onPositionChanged(qint64, qint64)));

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
    m_layout->addWidget(m_audioControls);
    setLayout(m_layout);

    m_musicLibrary = new MusicLibrary();

    m_musicPlayer = new MusicPlayer();
}

void MainWindow::onCoverClicked(const Album &album)
{
    m_trackView->show();
    m_trackView->onAlbumSelected(album);
    m_scrollArea->hide();

    foreach(Track* i_track, album.tracks())
        qDebug()<< i_track->title();
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

        emit this->trackAdded(*track);
    }
}

void MainWindow::onBackwardClicked()
{/*
    this->musicPlayer->getMediaPlayer()->setPosition(0);*/
}

void MainWindow::onPlayClicked()
{/*
    this->musicPlayer->getMediaPlayer()->play();*/
}

void MainWindow::onPauseClicked()
{/*
    this->musicPlayer->getMediaPlayer()->pause();*/
}

void MainWindow::onForwardClicked()
{/*
    this->musicPlayer->getMediaPlaylist()->next();*/
}

void MainWindow::onMusicSliderMoved(int position, int minimum, int maximum)
{/*
    if(maximum - minimum != 0) {
        this->musicPlayer->getMediaPlayer()->setPosition((this->musicPlayer->getMediaPlayer()->duration() * position) / (maximum - minimum));
    }*/
}

void MainWindow::onShuffleClicked(AudioControls::ShuffleMode_t shuffleMode)
{/*
    switch (shuffleMode)
    {
    case AudioControls::SHUFFLE_OFF: {
        this->musicPlayer->getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    }

    case AudioControls::SHUFFLE_ON: {
        this->musicPlayer->getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::Random);
        break;
    }

    default: {
        break;
    }
    }*/
}

void MainWindow::onRepeatClicked(AudioControls::RepeatMode_t repeatMode)
{/*
    switch (repeatMode)
    {
    case AudioControls::REPEAT_NONE: {
        this->musicPlayer->getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    }

    case AudioControls::REPEAT_ONE: {
        this->musicPlayer->getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    }

    case AudioControls::REPEAT_ALL: {
        this->musicPlayer->getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    }

    default: {
        break;
    }
    }*/
}

void MainWindow::onVolumeClicked(AudioControls::VolumeMode_t volumeMode)
{/*
    switch (volumeMode)
    {
    case AudioControls::VOLUME_MUTED: {
        this->musicPlayer->getMediaPlayer()->setMuted(true);
        break;
    }

    case AudioControls::VOLUME_NOT_MUTED: {
        this->musicPlayer->getMediaPlayer()->setMuted(false);
        break;
    }

    default: {
        break;
    }
    }*/
}

void MainWindow::onCurrentMediaChanged(QMediaContent mediaContent)
{
    QString filename {mediaContent.canonicalUrl().toString().split('/').last()};

    //for(QVector<Track>::iterator track {this->playlist->getTracks()->begin()}; track != this->playlist->getTracks()->end(); ++track) {
    /*if(track->getFilename() == filename) {
      emit this->currentMediaChanged(*track);
    }*/
    //}
}




void MainWindow::mediaPlayerPositionChanged(qint64 position)
{/*
    emit this->positionChanged(position, this->musicPlayer->getMediaPlayer()->duration());*/
}

void MainWindow::musicSliderMoved(int value)
{
    value++;
    //this->musicPlayer->getMediaPlayer()->setPosition((this->musicPlayer->getMediaPlayer()->duration() * value) / (this->musicSlider->maximum() - this->musicSlider->minimum()));
}

void MainWindow::musicSliderPressed()
{/*
    QObject::disconnect(this->musicPlayer->getMediaPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(mediaPlayerPositionChanged(qint64)));*/
}

void MainWindow::musicSliderReleased()
{/*
    QObject::connect(this->musicPlayer->getMediaPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(mediaPlayerPositionChanged(qint64)));*/
}

void MainWindow::volumeSliderMoved(int value)
{/*
    this->musicPlayer->getMediaPlayer()->setVolume(value);*/
}

void MainWindow::volumeValueChanged(int value)
{/*
    this->musicPlayer->getMediaPlayer()->setVolume(value);*/
}

void MainWindow::trackListItemDoubleClicked(const QModelIndex& index)
{
    qDebug() << index.row();
    // qDebug() << this->items.at(index.row())->getTrack()->getTitle();
    /*for(int i {0}; i < this->trackList->count(); i++) {
    if(item->text() == this->trackList->item(i)->text()) {
      this->musicPlayer->getMediaPlaylist()->setCurrentIndex(i);
      this->musicPlayer->getMediaPlayer()->play();

      //this->play->hide();
      //this->stop->show();

      break;
    }
  }*/
}

void MainWindow::playClicked()
{
    // this->musicPlayer->getMediaPlayer()->play();

    //this->play->hide();
    //this->stop->show();
}

void MainWindow::stopClicked()
{
    // this->musicPlayer->getMediaPlayer()->pause();

    //this->stop->hide();
    //this->play->show();
}

void MainWindow::previousClicked()
{/*
    this->musicPlayer->getMediaPlaylist()->previous();

    if(this->musicPlayer->getMediaPlaylist()->currentIndex() == -1) {
        //this->play->show();
        //this->stop->hide();
        //this->musicSlider->setValue(0);
    } else if(this->musicPlayer->getMediaPlaylist()->currentIndex() == 0 || this->musicPlayer->getMediaPlaylist()->currentIndex() == this->trackList->count() - 1) {
        this->musicPlayer->getMediaPlayer()->play();
        //this->play->hide();
        //this->stop->show();
    } else {
        this->musicPlayer->getMediaPlayer()->play();
    }

    this->trackList->setCurrentRow(this->musicPlayer->getMediaPlaylist()->currentIndex());*/
}

void MainWindow::nextClicked()
{/*
    this->musicPlayer->getMediaPlaylist()->next();

    if(this->musicPlayer->getMediaPlaylist()->currentIndex() == -1) {
        //this->play->show();
        //this->stop->hide();
        //this->musicSlider->setValue(0);
    } else if(this->musicPlayer->getMediaPlaylist()->currentIndex() == 0 || this->musicPlayer->getMediaPlaylist()->currentIndex() == this->trackList->count() - 1) {
        this->musicPlayer->getMediaPlayer()->play();
        //this->play->hide();
        //this->stop->show();
    } else {
        this->musicPlayer->getMediaPlayer()->play();
    }

    this->trackList->setCurrentRow(this->musicPlayer->getMediaPlaylist()->currentIndex());*/
}


void MainWindow::addSongClicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Select Track to Import"));

    for(QStringList::iterator filename {filenames.begin()}; filename != filenames.end(); filename++) {
        QFileInfo fileInfo {*filename};

        QVariantMap tags = TagUtils::readTags(fileInfo).toMap();
        Track* t = this->m_musicLibrary->addTrack(tags);
        if(t!=NULL) {
            qDebug()<<"tv"<<t->artist();
            /*TrackItem* ti = new TrackItem(*t);
      this->model->appendRow(ti->getItems());
*/
            /*  this->m_musicLibrary->debug();
      this->items.push_back(ti);

      //this->m_albumView->onTrackAdded(*t);
      */
            this->m_albumView->onTrackAdded(*t);
        }
        //Track track = Track(tags);

        //l->setPixmap(ImageUtils::stringToImage(QImage("images/white.png"), track.getTitle()));




        //qDebug() << track.getTitle();
        //qDebug() << track.getAlbum()->getTitle();
        /*
    QDir dir {fileInfo.absoluteDir()};
    QStringList data {dir.filePath(*filename).split('/')};

    QString title = QString(data.at(data.length() - Playlist::TITLE_INDEX)).mid(5);
    title = title.left(title.length() - 4);
    //Track track = Track(QString(data.at(data.length() - Playlist::ARTIST_INDEX)), QString(data.at(data.length() - Playlist::ALBUM_INDEX)), title, QString(data.at(data.length() - Playlist::TITLE_INDEX)), dir.filePath(*filename), QUrl(fileInfo.absoluteFilePath()));

    //this->playlist->addTrack(track);

    //this->musicPlayer->addTrack(track);

    //this->trackList->addItem(track.getTitle());
    //this->addSong->hide();
    this->remove->hide();
    */
    }
    /*
    if(this->musicPlayer->getMediaPlaylist()->currentIndex() == -1) {
        this->musicPlayer->getMediaPlaylist()->setCurrentIndex(0);
    }
    */
}

void MainWindow::addDirectoryClicked()
{/*
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Directory for Tracks to Import"));

    if(not directory.isEmpty()) {
        QDir dir {directory};

        QStringList filenames = dir.entryList(QStringList() << "*.mp3", QDir::Files);

        for(QStringList::iterator filename {filenames.begin()}; filename != filenames.end(); ++filename) {
            QFileInfo fileInfo {*filename};

            QDir dir {fileInfo.absoluteDir()};
            QStringList data {dir.filePath(*filename).split('/')};

            QString title = QString(data.at(data.length() - Playlist::TITLE_INDEX)).mid(5);
            title = title.left(title.length() - 4);
            //Track track = Track(QString(data.at(data.length() - Playlist::ARTIST_INDEX)), QString(data.at(data.length() - Playlist::ALBUM_INDEX)), title, QString(data.at(data.length() - Playlist::TITLE_INDEX)), dir.filePath(*filename), QUrl(fileInfo.absoluteFilePath()));

            //this->playlist->addTrack(track);

            //this->musicPlayer->addTrack(track);

            //this->trackList->addItem(track.getTitle());
        }

        if(this->musicPlayer->getMediaPlaylist()->currentIndex() == -1) {
            this->musicPlayer->getMediaPlaylist()->setCurrentIndex(0);
        }
    }*/
}

void MainWindow::removeClicked()
{
    //////QModelIndexList list = this->m_trackView->selectionModel()->selectedRows();

    //for(qint16 i = list.size() - 1; i >= 0; --i) {
    //this->items.removeAt(list.at(i).row());
    //this->model->removeRow(list.at(i).row());
    //}
}

void MainWindow::removeAllClicked()
{/*
    this->trackList->clear();
    this->musicPlayer->removeAllTracks();
    this->playlist->removeAllTracks();*/
}

void MainWindow::savePlaylistClicked()
{/*
    SavePlaylistWindow* savePlaylist = new SavePlaylistWindow(this->stackedWidget, this->playlist);

    this->stackedWidget->stackedWidget()->addWidget(savePlaylist);
    this->stackedWidget->stackedWidget()->setCurrentWidget(savePlaylist);*/
}

void MainWindow::loadPlaylistClicked()
{/*
    LoadPlaylistWindow* loadPlaylist = new LoadPlaylistWindow(this->stackedWidget);

    QObject::connect(loadPlaylist, SIGNAL(playlistLoaded(QString)), this, SLOT(playlistLoaded(QString)));

    this->stackedWidget->stackedWidget()->addWidget(loadPlaylist);
    this->stackedWidget->stackedWidget()->setCurrentWidget(loadPlaylist);*/
}

void MainWindow::playlistLoaded(QString playlistName)
{/*
    QString path {QDir::currentPath() + "/tracks/"};

    QDir dir {path + playlistName};

    QStringList filenames = dir.entryList(QStringList() << "*.mp3", QDir::Files);
    this->trackList->addItems(filenames);

    for(QStringList::iterator filename {filenames.begin()}; filename != filenames.end(); ++filename) {
        QFileInfo fileInfo {*filename};
        QStringList data {dir.filePath(*filename).split('/')};

        QString title = QString(data.at(data.length() - Playlist::TITLE_INDEX)).mid(5);
        title = title.left(title.length() - 4);

        //Track track = Track(QString(data.at(data.length() - Playlist::ARTIST_INDEX)), QString(data.at(data.length() - Playlist::ALBUM_INDEX)), title, QString(data.at(data.length() - Playlist::TITLE_INDEX)), dir.filePath(*filename), QUrl(fileInfo.absoluteFilePath()));

        //this->playlist->addTrack(track);
        //this->musicPlayer->addTrack(track);
    }*/
}
