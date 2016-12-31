#include "LeftPanel.h"

#include <QApplication>
#include <QFont>

LeftPanel::LeftPanel(QWidget* parent) : QWidget(parent)
{
    QFont font = QApplication::font();
    font.setPointSize(13);

    m_spacer0 = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_collection = new QLabel("Collection");
    m_collection->setFont(font);
    m_collection->setStyleSheet(QString("color: white;"));

    m_spacer1 = new QSpacerItem(0, 12, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_artists = new QLabel("   Artists");
    m_artists->setFont(font);
    m_artists->setStyleSheet(QString("color: white;"));

    m_spacer2 = new QSpacerItem(0, 6, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_albums = new QLabel("   Albums");
    m_albums->setFont(font);
    m_albums->setStyleSheet(QString("color: white;"));

    m_spacer3 = new QSpacerItem(0, 6, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_tracks = new QLabel("   Tracks");
    m_tracks->setFont(font);
    m_tracks->setStyleSheet(QString("color: white;"));

    m_spacer4 = new QSpacerItem(0, 6, QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_layout = new QVBoxLayout();
    m_layout->addItem(m_spacer0);
    m_layout->addWidget(m_collection);
    m_layout->addItem(m_spacer1);
    m_layout->addWidget(m_artists);
    m_layout->addItem(m_spacer2);
    m_layout->addWidget(m_albums);
    m_layout->addItem(m_spacer3);
    m_layout->addWidget(m_tracks);

    m_layout->addItem(m_spacer4);

    setLayout(m_layout);
}

LeftPanel::~LeftPanel()
{

}
