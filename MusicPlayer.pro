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
    albumview/Cover.cpp \
    audio/AudioControls.cpp \
    audio/AudioEngine.cpp \
    audio/TrackSlider.cpp \
    data/Album.cpp \
    data/Artist.cpp \
    data/MusicLibrary.cpp \
    data/Playlist.cpp \
    data/Track.cpp \
    data/TrackLoader.cpp \
    data/TrackLoaderThread.cpp \
    trackview/TrackAlbum.cpp \
    trackview/TrackDelegate.cpp \
    trackview/TrackItem.cpp \
    trackview/TrackList.cpp \
    trackview/TrackLyrics.cpp \
    trackview/TrackModel.cpp \
    trackview/TrackView.cpp \
    utils/ImageUtils.cpp \
    utils/TagUtils.cpp \
    utils/Utils.cpp \
    widgets/BackgroundWidget.cpp \
    widgets/ClickableLabel.cpp \
    widgets/ElidedLabel.cpp \
    widgets/ImageButton.cpp \
    widgets/ScrollableArea.cpp \
    widgets/Slider.cpp \
    widgets/StackedWidget.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS  += albumview/AlbumView.h \
    albumview/Cover.h \
    audio/AudioControls.h \
    audio/AudioEngine.h \
    audio/TrackSlider.h \
    data/Album.h \
    data/Artist.h \
    data/MusicLibrary.h \
    data/Playlist.h \
    data/Track.h \
    data/TrackLoader.h \
    data/TrackLoaderThread.h \
    trackview/TrackDelegate.h \
    trackview/TrackItem.h \
    trackview/TrackView.h \
    trackview/TrackLyrics.h \
    trackview/TrackList.h \
    trackview/TrackModel.h \
    trackview/TrackAlbum.h \
    utils/GuiUtils.h \
    utils/ImageUtils.h \
    utils/TagUtils.h \
    utils/Utils.h \
    widgets/BackgroundWidget.h \
    widgets/ClickableLabel.h \
    widgets/ElidedLabel.h \
    widgets/ImageButton.h \
    widgets/Slider.h \
    widgets/ScrollableArea.h \
    widgets/StackedWidget.h \
    MainWindow.h

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

LIBS += -L$$PWD/taglib/lib/ -lTagLib

INCLUDEPATH += $$PWD/taglib/include
DEPENDPATH += $$PWD/taglib/include
