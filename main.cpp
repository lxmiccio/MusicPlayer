#include <QApplication>
#include <QFontDatabase>

#include "StackedWidget.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

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
