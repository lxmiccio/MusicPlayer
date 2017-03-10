#include "ArtistAlbumsView.h"

ArtistAlbumsView::ArtistAlbumsView(QWidget* parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(16, 0, 0, 0);
    m_layout->setSpacing(16);
    setLayout(m_layout);
}

void ArtistAlbumsView::clearLayout(QLayout* layout)
{
    QLayoutItem* i_item;

    while((i_item = layout->takeAt(0)) != NULL)
    {
        if(i_item->layout())
        {
            clearLayout(i_item->layout());
            delete i_item->layout();
        }
        if(i_item->widget())
        {
            delete i_item->widget();
        }

        delete i_item;
    }
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

                if(i != widgetsToAdd - 1)
                {
                    Line* line = new Line(Qt::Horizontal);
                    m_horizontalLines.push_back(line);
                }
            }
        }

        for(quint8 i = 0; i < artist->albums().size(); i++)
        {
            m_widgets.at(i)->setAlbum(artist->albums().at(i));
            m_layout->addWidget(m_widgets.at(i));

            if(i != artist->albums().size() - 1)
            {
               m_layout->addWidget(m_horizontalLines.at(i));
            }
        }

        locker.unlock();
    }
}
