#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QFontDatabase>
#include <QTime>

#include "MainWindow.h"
#include "Track.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    qRegisterMetaType<QFileInfo>("QFileInfo");
    qRegisterMetaType<Track*>("Track");

    QFontDatabase::addApplicationFont(":/fonts/sniglet-regular.ttf");
    QFont font = QApplication::font();
    font.setFamily("Sniglet");
    font.setPointSize(9);
    font.setStyleStrategy(QFont::PreferAntialias);
    QApplication::setFont(font);

    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return application.exec();

    /* TODO here
     * Load album cover when loading tracks
     * Fix awful TrackSlider behaviour when a track starts, which is probably due to the slot TrackSlider::onTrackStarted(...) invoked twice
     * Bug: if there is one song and user skips it, TrackSliders starts moving even if track is not playing
     */
}
