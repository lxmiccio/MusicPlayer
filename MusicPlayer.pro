#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T12:08:17
#
#-------------------------------------------------

QT       += core concurrent gui multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 010-MusicPlayer
TEMPLATE = app

SOURCES += albumview/AlbumView.cpp \
    albumview/Cover.cpp \
    audio/AudioControls.cpp \
    audio/AudioEngine.cpp \
    audio/AudioManager.cpp \
    audio/TrackSlider.cpp \
    data/Album.cpp \
    data/Artist.cpp \
    data/MusicLibrary.cpp \
    data/Track.cpp \
    data/TrackLoader.cpp \
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
    widgets/ScrollableArea.cpp \
    widgets/Slider.cpp \
    widgets/StackedWidget.cpp \
    main.cpp \
    mainwindow.cpp \
    playlist.cpp \
    utils/Utils.cpp \
    trackview/TrackLyrics.cpp \
    data/TrackLoaderThread.cpp

HEADERS  += albumview/AlbumView.h \
    albumview/Cover.h \
    audio/AudioControls.h \
    audio/AudioEngine.h \
    audio/AudioManager.h \
    audio/TrackSlider.h \
    data/Album.h \
    data/Artist.h \
    data/MusicLibrary.h \
    data/Track.h \
    data/TrackLoader.h \
    data/TrackLoaderThread.h \
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
    widgets/ScrollableArea.h \
    widgets/Slider.h \
    widgets/StackedWidget.h \
    mainwindow.h \
    playlist.h \
    utils/Utils.h \
    trackview/TrackLyrics.h

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

unix|win32: LIBS += -L$$PWD/taglib/lib/ -lTagLib

INCLUDEPATH += $$PWD/taglib/include
DEPENDPATH += $$PWD/taglib/include
