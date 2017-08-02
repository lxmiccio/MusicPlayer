#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T12:08:18
#
#-------------------------------------------------

QT       += core concurrent gui multimedia network svg

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
    audio/AudioControls.cpp \
    audio/AudioEngine.cpp \
    data/Album.cpp \
    data/Artist.cpp \
    data/MusicLibrary.cpp \
    data/Playlist.cpp \
    data/Track.cpp \
    mp3lame/LameWrapper.cpp \
    playingview/PlayingAlbum.cpp \
    playingview/PlayingLyrics.cpp \
    playingview/PlayingView.cpp \
    soundtouch/SoundTouchWrapper.cpp \
    utils/ImageUtils.cpp \
    utils/Settings.cpp \
    utils/Utils.cpp \
    widgets/BackgroundWidget.cpp \
    widgets/ClickableLabel.cpp \
    widgets/ClickableWidget.cpp \
    widgets/ElidedLabel.cpp \
    widgets/ImageButton.cpp \
    widgets/LineWidget.cpp \
    widgets/Slider.cpp \
    widgets/TrackSlider.cpp \
    taglib/TagLibWrapper.cpp \
    albumview/AlbumDelegate.cpp \
    api/HttpRequestInput.cpp \
    api/HttpRequestWorker.cpp \
    albumview/AlbumCoverWidget.cpp \
    albumview/AlbumTableItem.cpp \
    data/PlaylistManager.cpp \
    playlistview/PlaylistView.cpp \
    views/TrackInfoView.cpp \
    views/trackslist/TracksListView.cpp \
    views/trackslist/TracksListDelegate.cpp \
    views/trackslist/TracksListItem.cpp \
    views/trackslist/TracksListModel.cpp \
    widgets/ScrollableWidget.cpp \
    views/artistslist/ArtistsListDelegate.cpp \
    views/artistslist/ArtistsListItem.cpp \
    views/artistslist/ArtistsListModel.cpp \
    views/artistslist/ArtistsListView.cpp \
    views/AlbumInfoView.cpp \
    views/albumstrackslist/AlbumsTracksListDelegate.cpp \
    views/albumstrackslist/AlbumsTracksListItem.cpp \
    views/albumstrackslist/AlbumsTracksListModel.cpp \
    views/albumstrackslist/AlbumsTracksListView.cpp

HEADERS  += albumview/AlbumCover.h \
    albumview/AlbumGrid.h \
    albumview/AlbumTracks.h \
    albumview/AlbumView.h \
    artistview/ArtistAlbumsView.h \
    artistview/ArtistAlbumWidget.h \
    artistview/ArtistView.h \
    audio/AudioControls.h \
    audio/AudioEngine.h \
    data/Album.h \
    data/Artist.h \
    data/MusicLibrary.h \
    data/Playlist.h \
    data/Track.h \
    MainWidget.h \
    MainWindow.h \
    mp3lame/LameWrapper.h \
    playingview/PlayingAlbum.h \
    playingview/PlayingLyrics.h \
    playingview/PlayingView.h \
    soundtouch/SoundTouchWrapper.h \
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
    widgets/Slider.h \
    widgets/TrackSlider.h \
    taglib/TagLibWrapper.h \
    albumview/AlbumDelegate.h \
    api/HttpRequestInput.h \
    api/HttpRequestWorker.h \
    albumview/AlbumCoverWidget.h \
    albumview/AlbumTableItem.h \
    data/PlaylistManager.h \
    PlaylistView.h \
    playlistview/PlaylistView.h \
    views/TrackInfoView.h \
    views/trackslist/TracksListView.h \
    views/trackslist/TracksListDelegate.h \
    views/trackslist/TracksListItem.h \
    views/trackslist/TracksListModel.h \
    widgets/ScrollableWidget.h \
    views/artistslist/ArtistsListDelegate.h \
    views/artistslist/ArtistsListItem.h \
    views/artistslist/ArtistsListModel.h \
    views/artistslist/ArtistsListView.h \
    views/AlbumInfoView.h \
    views/albumstrackslist/AlbumsTracksListDelegate.h \
    views/albumstrackslist/AlbumsTracksListItem.h \
    views/albumstrackslist/AlbumsTracksListModel.h \
    views/albumstrackslist/AlbumsTracksListView.h

INCLUDEPATH += $$PWD/albumview
INCLUDEPATH += $$PWD/api
INCLUDEPATH += $$PWD/artistview
INCLUDEPATH += $$PWD/audio
INCLUDEPATH += $$PWD/data
INCLUDEPATH += $$PWD/engine
INCLUDEPATH += $$PWD/gui
INCLUDEPATH += $$PWD/mp3lame
INCLUDEPATH += $$PWD/playingview
INCLUDEPATH += $$PWD/playlistview
INCLUDEPATH += $$PWD/soundtouch
INCLUDEPATH += $$PWD/taglib
INCLUDEPATH += $$PWD/utils
INCLUDEPATH += $$PWD/views
INCLUDEPATH += $$PWD/views/albumstrackslist
INCLUDEPATH += $$PWD/views/artistslist
INCLUDEPATH += $$PWD/views/trackslist
INCLUDEPATH += $$PWD/widgets

RESOURCES += resources.qrc

include($$PWD/../QHotkey/qhotkey.pri)

INCLUDEPATH += $$PWD/../QMp3Lame/frontend \
               $$PWD/../QMp3Lame/include \
               $$PWD/../QMp3Lame/libmp3lame \
               $$PWD/../QSoundTouch/include \
               $$PWD/../QSoundTouch/source/SoundStretch \
               $$PWD/../QSoundTouch/source/SoundTouch \
               $$PWD/../QTagLib \
               $$PWD/../QTagLib/taglib \
               $$PWD/../QTagLib/taglib/ape \
               $$PWD/../QTagLib/taglib/asf \
               $$PWD/../QTagLib/taglib/flac \
               $$PWD/../QTagLib/taglib/it \
               $$PWD/../QTagLib/taglib/mod \
               $$PWD/../QTagLib/taglib/mp4 \
               $$PWD/../QTagLib/taglib/mpc \
               $$PWD/../QTagLib/taglib/mpeg \
               $$PWD/../QTagLib/taglib/mpeg/id3v1 \
               $$PWD/../QTagLib/taglib/mpeg/id3v2 \
               $$PWD/../QTagLib/taglib/mpeg/id3v2/frames \
               $$PWD/../QTagLib/taglib/ogg \
               $$PWD/../QTagLib/taglib/ogg/flac \
               $$PWD/../QTagLib/taglib/ogg/opus \
               $$PWD/../QTagLib/taglib/ogg/speex \
               $$PWD/../QTagLib/taglib/ogg/vorbis \
               $$PWD/../QTagLib/taglib/riff \
               $$PWD/../QTagLib/taglib/riff/aiff \
               $$PWD/../QTagLib/taglib/riff/wav \
               $$PWD/../QTagLib/taglib/s3m \
               $$PWD/../QTagLib/taglib/toolkit \
               $$PWD/../QTagLib/taglib/trueaudio \
               $$PWD/../QTagLib/taglib/wavpack \
               $$PWD/../QTagLib/taglib/xm

LIBS += -L$$PWD/../QMp3Lame/release -llame-3.99.5
LIBS += -L$$PWD/../QSoundTouch/release/ -lsoundtouch
LIBS += -L$$PWD/../QTagLib/release -ltaglib-1.11.1

#LIBS += -L$$PWD/../mp3lame/release/release -L$$PWD/../mp3lame/release -lmp3lame
#LIBS += -L$$PWD/../SoundTouch/release/release -L$$PWD/../SoundTouch/release -lSoundTouch
#LIBS += -L$$PWD/../QTagLib/release -L$$PWD/../QTagLib/release/release -ltaglib-1.11.1
