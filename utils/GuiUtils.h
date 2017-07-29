#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QLayout>
#include <QString>
#include <QWidget>

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
                                             "margin: 0px 0px 0px 0px;"
                                             "width: 10px;"
                                             "}"
                                             "QScrollBar::handle:vertical {"
                                             "border-image: url(:/images/scroll-bar.jpg);"
                                             "border-radius: 2px;"
                                             "margin: 0px 2px 0px 2px;"
                                             "}"
                                             "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,"
                                             "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                                             "border: 0px;"
                                             "height: 0px;"
                                             "width: 0px;"
                                             "}");

    const QString SLIDER_STYLE = QString("QSlider::groove:horizontal {"
                                         "background: rgba(200, 200, 200, 50);"
                                         "border-radius: 3px;"
                                         "}"
                                         "QSlider::handle:horizontal {"
                                         "background: #FFF;"
                                         "border-radius: 3px;"
                                         "width: 10px;"
                                         "}"
                                         "QSlider::sub-page:horizontal {"
                                         "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #777, stop: 1 #EEE);"
                                         "border-radius: 3px;"
                                         "}"
                                         );

    static void deleteLayout(QLayout* layout)
    {
        QLayoutItem* i_item;

        while((i_item = layout->takeAt(0)) != NULL)
        {
            if(i_item->layout())
            {
                deleteLayout(i_item->layout());
                delete i_item->layout();
            }

            if(i_item->widget())
            {
                delete i_item->widget();
            }

            delete i_item;
        }
    }
}

#endif// GUIUTILS_H
