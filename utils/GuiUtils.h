#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QString>

namespace GuiUtils
{
    const QString SCROLLABLE_AREA_STYLE = QString("QScrollArea {"
                                                  "background: transparent;"
                                                  "border: 0px;"
                                                  "}"
                                                  "QScrollArea > QWidget > QWidget {"
                                                  "background: transparent;"
                                                  "}");

    const QString SCROLL_BAR_STYLE = QString("QScrollBar:vertical {"
                                             "background: transparent;"
                                             "border: 0px;"
                                             "margin: 0px 0px 10px 0px;"
                                             "width: 10px;"
                                             "}"
                                             "QScrollBar::handle:vertical {"
                                             "border-image: url(:/images/scroll-bar.jpg);"
                                             "border-radius: 2px;"
                                             "margin: 2px 4px 2px 0px;"
                                             "}"
                                             "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,"
                                             "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                                             "border: 0px;"
                                             "height: 0px;"
                                             "width: 0px;"
                                             "}");

    const QString SLIDER_STYLE = QString("QSlider::groove:horizontal {"
                                         "background: rgba(200, 200, 200, 50);"
                                         "border-radius: 3px 3px 3px 3px;"
                                         "margin-bottom: 0px;"
                                         "margin-left: 0px;"
                                         "margin-right: 0px;"
                                         "margin-top: 0px;"
                                         "}"
                                         "QSlider::sub-page:horizontal {"
                                         "background: white;"
                                         "margin-bottom: 1px;"
                                         "margin-left: 1px;"
                                         "margin-right: 1px;"
                                         "margin-top: 1px;"
                                         "}");
}

#endif // GUIUTILS_H
