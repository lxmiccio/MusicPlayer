#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

class LeftPanel : public QWidget
{
    Q_OBJECT

    public:
        explicit LeftPanel(QWidget* parent = 0);
        ~LeftPanel();

    private:
        QSpacerItem* m_spacer0;
        QLabel* m_collection;
        QSpacerItem* m_spacer1;
        QLabel* m_artists;
        QSpacerItem* m_spacer2;
        QLabel* m_albums;
        QSpacerItem* m_spacer3;
        QLabel* m_tracks;
        QSpacerItem* m_spacer4;

        QVBoxLayout* m_layout;
};

#endif // LEFTPANEL_H
