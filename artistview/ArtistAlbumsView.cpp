#include "ArtistAlbumsView.h"

ArtistAlbumsView::ArtistAlbumsView(QWidget* parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    setLayout(m_layout);
}

ArtistAlbumsView::onArtistChanged(Artist *artist)
{
    if(artist)
    {
        for(quint8 i = 0; i < m_widgets.size(); ++i)
        {
            m_layout->removeWidget(m_widgets.at(i));
        }

        quint8 widgetsToAdd = artist->albums().size() - m_widgets.size();

        for(quint8 i = 0; i < widgetsToAdd; ++i)
        {
            ArtistAlbumWidget* widget = new ArtistAlbumWidget();
            m_widgets.push_back(widget);
            m_layout->addWidget(widget);
        }

        for(quint8 i = 0; i < artist->albums().size(); ++i) {
            m_widgets.at(i)->setAlbum(artist->albums().at(i));
        }
    }
}
