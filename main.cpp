#include <QApplication>
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
    qsrand((uint) time.msec());

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return application.exec();

    /* TODO: Move the scrollbar containing ArtistView from MainWidget to ArtistView.
     * Introduce TrackView on the MenuBar.
     * Move LoaderThread to MusicLibrary, so that all the views will use the same. */
}
