#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T12:08:17
#
#-------------------------------------------------

QT       += core gui multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 010-MusicPlayer
TEMPLATE = app

SOURCES += main.cpp\
    albumview/AlbumView.cpp \
    albumview/Cover.cpp \
    audio/AudioControls.cpp \
    audio/AudioEngine.cpp \
    audio/MusicPlayer.cpp \
    data/Album.cpp \
    data/Artist.cpp \
    data/MusicLibrary.cpp \
    data/Track.cpp \
    trackview/TrackAlbum.cpp \
    trackview/TrackDelegate.cpp \
    trackview/TrackItem.cpp \
    trackview/TrackList.cpp \
    trackview/TrackModel.cpp \
    trackview/TrackView.cpp \
    utils/ImageUtils.cpp \
    utils/TagUtils.cpp \
    widgets/BackgroundWidget.cpp \
    widgets/ClickableLabel.cpp \
    widgets/ElidedLabel.cpp \
    widgets/ImageButton.cpp \
    widgets/LeftPanel.cpp \
    widgets/ScrollArea.cpp \
    widgets/SeekSlider.cpp \
    widgets/StackedWidget.cpp \
    loadplaylistwindow.cpp \
    mainwindow.cpp \
    playlist.cpp \
    saveplaylistwindow.cpp \
    widgets/Slider.cpp

HEADERS  += albumview/AlbumView.h \
    albumview/Cover.h \
    audio/AudioControls.h \
    audio/AudioEngine.h \
    audio/MusicPlayer.h \
    data/Album.h \
    data/Artist.h \
    data/MusicLibrary.h \
    data/Track.h \
    trackview/TrackDelegate.h \
    trackview/TrackItem.h \
    trackview/TrackView.h \
    trackview/TrackList.h \
    trackview/TrackModel.h \
    trackview/TrackAlbum.h \
    utils/ImageUtils.h \
    utils/TagUtils.h \
    widgets/BackgroundWidget.h \
    widgets/ClickableLabel.h \
    widgets/ElidedLabel.h \
    widgets/ImageButton.h \
    widgets/LeftPanel.h \
    widgets/ScrollArea.h \
    widgets/SeekSlider.h \
    widgets/StackedWidget.h \
    loadplaylistwindow.h \
    mainwindow.h \
    playlist.h \
    saveplaylistwindow.h \
    widgets/Slider.h

INCLUDEPATH += $$PWD/albumview
INCLUDEPATH += $$PWD/audio
INCLUDEPATH += $$PWD/data
INCLUDEPATH += $$PWD/engine
INCLUDEPATH += $$PWD/gui
INCLUDEPATH += $$PWD/table
INCLUDEPATH += $$PWD/tag
INCLUDEPATH += $$PWD/trackview
INCLUDEPATH += $$PWD/utils
INCLUDEPATH += $$PWD/widgets

RESOURCES += resources.qrc

INCLUDEPATH += $$PWD/taglib/include

LIBS += -L$$PWD/taglib/lib -ltaglib

