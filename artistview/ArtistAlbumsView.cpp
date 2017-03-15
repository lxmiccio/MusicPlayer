#include "ArtistAlbumsView.h"

ArtistAlbumsView::ArtistAlbumsView(QWidget* parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(20, 0, 40, 0);
    m_layout->setSpacing(0);
    setLayout(m_layout);
}

ArtistAlbumsView::~ArtistAlbumsView()
{
    clearLayout(m_layout);
}

const Artist* ArtistAlbumsView::artist() const
{
    return c_artist;
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
    QMutexLocker locker(&m_mutex);
    clearLayout(m_layout);

    if(artist)
    {
        c_artist = artist;

        m_widgets.clear();
        m_lines.clear();

        for(quint8 i = 0; i < artist->albums().size(); i++)
        {
            ArtistAlbumWidget* widget = new ArtistAlbumWidget();
            widget->setAlbum(artist->albums().at(i));
            m_widgets.push_back(widget);
            m_layout->addWidget(widget);

            if(i !=  artist->albums().size() - 1)
            {
                Line* line = new Line(Qt::Horizontal);
                m_lines.push_back(line);
                m_layout->addWidget(line);
            }
        }
    }
}
