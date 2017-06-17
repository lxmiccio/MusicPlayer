#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T12:08:18
#
#-------------------------------------------------

QT       += core concurrent gui multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 010-MusicPlayer
TEMPLATE = app

SOURCES += main.cpp \
    MainWidget.cpp \
    MainWindow.cpp \
    albumview/AlbumCover.cpp \
    albumview/AlbumGrid.cpp \
    albumview/AlbumTracks.cpp \
    albumview/AlbumView.cpp \
    artistview/ArtistAlbumsView.cpp \
    artistview/ArtistAlbumWidget.cpp \
    artistview/ArtistView.cpp \
    artistview/ArtistWidget.cpp \
    audio/AudioControls.cpp \
    audio/AudioEngine.cpp \
    data/Album.cpp \
    data/Artist.cpp \
    data/MusicLibrary.cpp \
    data/Playlist.cpp \
    data/Track.cpp \
    data/TrackLoader.cpp \
    data/TrackLoaderThread.cpp \
    mp3lame/LameWrapper.cpp \
    playingview/PlayingAlbum.cpp \
    playingview/PlayingLyrics.cpp \
    playingview/PlayingView.cpp \
    soundtouch/SoundTouchManager.cpp \
    soundtouch/SoundTouchWrapper.cpp \
    trackview/TrackDelegate.cpp \
    trackview/TrackFilterProxy.cpp \
    trackview/TrackItem.cpp \
    trackview/TrackModel.cpp \
    trackview/TrackView.cpp \
    utils/ImageUtils.cpp \
    utils/Settings.cpp \
    utils/Utils.cpp \
    widgets/BackgroundWidget.cpp \
    widgets/ClickableLabel.cpp \
    widgets/ClickableWidget.cpp \
    widgets/ElidedLabel.cpp \
    widgets/ImageButton.cpp \
    widgets/LineWidget.cpp \
    widgets/ScrollableArea.cpp \
    widgets/Slider.cpp \
    widgets/TrackSlider.cpp \
    taglib/TagLibWrapper.cpp \
    albumview/AlbumDelegate.cpp

HEADERS  += albumview/AlbumCover.h \
    albumview/AlbumGrid.h \
    albumview/AlbumTracks.h \
    albumview/AlbumView.h \
    artistview/ArtistAlbumsView.h \
    artistview/ArtistAlbumWidget.h \
    artistview/ArtistView.h \
    artistview/ArtistWidget.h \
    audio/AudioControls.h \
    audio/AudioEngine.h \
    data/Album.h \
    data/Artist.h \
    data/MusicLibrary.h \
    data/Playlist.h \
    data/Track.h \
    data/TrackLoader.h \
    data/TrackLoaderThread.h \
    MainWidget.h \
    MainWindow.h \
    mp3lame/LameWrapper.h \
    playingview/PlayingAlbum.h \
    playingview/PlayingLyrics.h \
    playingview/PlayingView.h \
    soundtouch/SoundTouchManager.h \
    soundtouch/SoundTouchWrapper.h \
    trackview/TrackDelegate.h \
    trackview/TrackFilterProxy.h \
    trackview/TrackItem.h \
    trackview/TrackModel.h \
    trackview/TrackView.h \
    utils/GuiUtils.h \
    utils/ImageUtils.h \
    utils/Settings.h \
    utils/Utils.h \
    widgets/BackgroundWidget.h \
    widgets/ClickableLabel.h \
    widgets/ClickableWidget.h \
    widgets/ElidedLabel.h \
    widgets/ImageButton.h \
    widgets/LineWidget.h \
    widgets/ScrollableArea.h \
    widgets/Slider.h \
    widgets/TrackSlider.h \
    taglib/TagLibWrapper.h \
    albumview/AlbumDelegate.h

INCLUDEPATH += $$PWD/albumview
INCLUDEPATH += $$PWD/artistview
INCLUDEPATH += $$PWD/audio
INCLUDEPATH += $$PWD/data
INCLUDEPATH += $$PWD/engine
INCLUDEPATH += $$PWD/gui
INCLUDEPATH += $$PWD/mp3lame
INCLUDEPATH += $$PWD/playingview
INCLUDEPATH += $$PWD/soundtouch
INCLUDEPATH += $$PWD/taglib
INCLUDEPATH += $$PWD/trackview
INCLUDEPATH += $$PWD/utils
INCLUDEPATH += $$PWD/widgets

RESOURCES += resources.qrc

include($$PWD/../QHotkey/qhotkey.pri)

INCLUDEPATH += $$PWD/../mp3lame/libmp3lame \
               $$PWD/../mp3lame/utils \
               $$PWD/../SoundTouch/include \
               $$PWD/../SoundTouch/source/SoundStretch \
               $$PWD/../SoundTouch/source/SoundTouch \
               $$PWD/../TagLib/taglib \
               $$PWD/../TagLib/taglib/ape \
               $$PWD/../TagLib/taglib/asf \
               $$PWD/../TagLib/taglib/flac \
               $$PWD/../TagLib/taglib/it \
               $$PWD/../TagLib/taglib/mod \
               $$PWD/../TagLib/taglib/mp4 \
               $$PWD/../TagLib/taglib/mpc \
               $$PWD/../TagLib/taglib/mpeg \
               $$PWD/../TagLib/taglib/mpeg/id3v1 \
               $$PWD/../TagLib/taglib/mpeg/id3v2 \
               $$PWD/../TagLib/taglib/mpeg/id3v2/frames \
               $$PWD/../TagLib/taglib/ogg \
               $$PWD/../TagLib/taglib/ogg/flac \
               $$PWD/../TagLib/taglib/ogg/opus \
               $$PWD/../TagLib/taglib/ogg/speex \
               $$PWD/../TagLib/taglib/ogg/vorbis \
               $$PWD/../TagLib/taglib/riff \
               $$PWD/../TagLib/taglib/riff/aiff \
               $$PWD/../TagLib/taglib/riff/wav \
               $$PWD/../TagLib/taglib/s3m \
               $$PWD/../TagLib/taglib/toolkit \
               $$PWD/../TagLib/taglib/trueaudio \
               $$PWD/../TagLib/taglib/wavpack \
               $$PWD/../TagLib/taglib/xm

LIBS += -L$$PWD/../mp3lame/release -L$$PWD/../mp3lame/release/release -lmp3lame
LIBS += -L$$PWD/../SoundTouch/release/ -L$$PWD/../SoundTouch/release/release -lSoundTouch
LIBS += -L$$PWD/../TagLib/release -L$$PWD/../TagLib/release/release -lTagLib
