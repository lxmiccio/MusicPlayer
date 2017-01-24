#include <QApplication>
#include <QFileInfo>
#include <QFontDatabase>

#include "StackedWidget.h"
#include "Track.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    qRegisterMetaType<QFileInfo>("QFileInfo");
    qRegisterMetaType<Track>("Track");

    QFontDatabase::addApplicationFont(":/fonts/sniglet-regular.ttf");

    QFont font = QApplication::font();
    font.setFamily("Sniglet");
    font.setPointSize(9);
    font.setStyleStrategy(QFont::PreferAntialias);
    QApplication::setFont(font);

    StackedWidget stackedWidget;
    stackedWidget.show();

    return application.exec();
}
