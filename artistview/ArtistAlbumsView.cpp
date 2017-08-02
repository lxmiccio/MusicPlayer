#include "ArtistAlbumsView.h"

ArtistAlbumsView::ArtistAlbumsView(QWidget* parent) : QWidget(parent)
{
    m_artist = NULL;

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);
}

ArtistAlbumsView::~ArtistAlbumsView()
{
    clearLayout(m_layout);
}

Artist* ArtistAlbumsView::artist() const
{
    return m_artist;
}

void ArtistAlbumsView::onArtistChanged(Artist* artist)
{
    QMutexLocker locker(&m_mutex);

    if(artist)
    {
        clearLayout(m_layout);
        m_widgets.clear();
        m_separators.clear();

        if(m_artist)
        {
            QObject::disconnect(m_artist, SIGNAL(albumAdded(Album*)), this, SLOT(onAlbumAdded(Album*)));
            QObject::disconnect(m_artist, SIGNAL(albumRemoved(Album*)), this, SLOT(onAlbumRemoved(Album*)));
        }

        m_artist = artist;
        QObject::connect(m_artist, SIGNAL(albumAdded(Album*)), SLOT(onAlbumAdded(Album*)));
        QObject::connect(m_artist, SIGNAL(albumRemoved(Album*)), SLOT(onAlbumRemoved(Album*)));

        for(quint8 i = 0; i < artist->albums().size(); ++i)
        {
            AlbumInfoView* widget = new AlbumInfoView();
            widget->changeAlbum(artist->albums().at(i));
            m_widgets.push_back(widget);

            m_layout->addWidget(widget);

            if(i != artist->albums().size() - 1)
            {
                LineWidget* separator = new LineWidget(Qt::Horizontal);
                m_separators.push_back(separator);

                m_layout->addWidget(separator);
            }
        }
    }
}

void ArtistAlbumsView::onAlbumAdded(Album* album)
{
    if(album)
    {
        /* TODO: Should add the new album instead of repaint them all. Check for alphabetical order before adding it */
        onArtistChanged(album->artist());
    }
}

void ArtistAlbumsView::onAlbumRemoved(Album* album)
{
    if(album)
    {
        quint16 index = widgetIndex(album);
        m_widgets.takeAt(index)->deleteLater();
        m_separators.takeAt(index)->deleteLater();
    }
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

qint16 ArtistAlbumsView::widgetIndex(Album* album)
{
    if(album)
    {
        for(qint16 i = 0; i < m_widgets.size(); ++i)
        {
            if(m_widgets.at(i)->album() == album)
            {
                return i;
            }
        }
    }

    return -1;
}
