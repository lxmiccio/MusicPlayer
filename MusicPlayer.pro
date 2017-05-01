#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T12:08:18
#
#-------------------------------------------------

QT       += core concurrent gui multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 010-MusicPlayer
TEMPLATE = app

SOURCES += albumview/AlbumView.cpp \
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
    playingview/PlayingView.cpp \
    playingview/PlayingAlbum.cpp \
    playingview/PlayingLyrics.cpp \
    trackview/TrackDelegate.cpp \
    trackview/TrackFilterProxy.cpp \
    trackview/TrackItem.cpp \
    trackview/TrackModel.cpp \
    trackview/TrackView.cpp \
    utils/ImageUtils.cpp \
    utils/Settings.cpp \
    utils/TagUtils.cpp \
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
    MainWidget.cpp \
    MainWindow.cpp \
    main.cpp \
    albumview/AlbumGrid.cpp \
    albumview/AlbumTracks.cpp \
    albumview/AlbumCover.cpp

HEADERS  += albumview/AlbumView.h \
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
    playingview/PlayingAlbum.h \
    playingview/PlayingLyrics.h \
    playingview/PlayingView.h \
    trackview/TrackDelegate.h \
    trackview/TrackFilterProxy.h \
    trackview/TrackItem.h \
    trackview/TrackModel.h \
    trackview/TrackView.h \
    utils/GuiUtils.h \
    utils/ImageUtils.h \
    utils/Settings.h \
    utils/TagUtils.h \
    utils/Utils.h \
    widgets/BackgroundWidget.h \
    widgets/ClickableLabel.h \
    widgets/ClickableWidget.h \
    widgets/ElidedLabel.h \
    widgets/ImageButton.h \
    widgets/LineWidget.h \
    widgets/Slider.h \
    widgets/ScrollableArea.h \
    widgets/TrackSlider.h \
    MainWidget.h \
    MainWindow.h \
    albumview/AlbumGrid.h \
    albumview/AlbumTracks.h \
    albumview/AlbumCover.h

INCLUDEPATH += $$PWD/albumview
INCLUDEPATH += $$PWD/artistview
INCLUDEPATH += $$PWD/audio
INCLUDEPATH += $$PWD/data
INCLUDEPATH += $$PWD/engine
INCLUDEPATH += $$PWD/gui
INCLUDEPATH += $$PWD/playingview
INCLUDEPATH += $$PWD/tag
INCLUDEPATH += $$PWD/trackview
INCLUDEPATH += $$PWD/utils
INCLUDEPATH += $$PWD/widgets

RESOURCES += resources.qrc

LIBS += -L$$PWD/taglib/lib/ -lTagLib

INCLUDEPATH += $$PWD/taglib/include
DEPENDPATH += $$PWD/taglib/include

include($$PWD/../QHotkey/qhotkey.pri)
