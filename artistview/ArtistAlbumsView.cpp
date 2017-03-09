#include "ArtistAlbumsView.h"

#include <QDebug>

ArtistAlbumsView::ArtistAlbumsView(QWidget* parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    setLayout(m_layout);
}

void ArtistAlbumsView::onArtistChanged(const Artist* artist)
{
    if(artist)
    {
        QMutexLocker locker(&m_mutex);

        clearLayout(m_layout);
        m_widgets.clear();

        for(quint8 i = 0; i < m_widgets.size(); i++)
        {
            m_layout->removeWidget(m_widgets.at(i));
        }

        if(artist->albums().size() > m_widgets.size())
        {
            quint8 widgetsToAdd = artist->albums().size() - m_widgets.size();

            for(quint8 i = 0; i < widgetsToAdd; i++)
            {
                ArtistAlbumWidget* widget = new ArtistAlbumWidget();
                m_widgets.push_back(widget);
                m_layout->addWidget(widget);
            }
        }

        for(quint8 i = 0; i < artist->albums().size(); i++) {
            m_widgets.at(i)->setAlbum(artist->albums().at(i));
            m_layout->addWidget(m_widgets.at(i));
        }

        locker.unlock();
    }
}
