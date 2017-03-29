#include <QApplication>
#include <QFileInfo>
#include <QFontDatabase>
#include <QTime>

#include "StackedWidget.h"
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

    StackedWidget stackedWidget;
    stackedWidget.showMaximized();

    return application.exec();

    /* TODO: MainWindow should be a QMainWindow in order to display the menu, not a QWidget.
     * Try to have a BackgroundWidget as a member of MainWindow and check if the menu inherits the background.
     * If not, have BackgroundWidgete to subclass QMainWindows instead that QWidget. */
}
