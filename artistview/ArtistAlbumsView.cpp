#include "ArtistAlbumsView.h"

ArtistAlbumsView::ArtistAlbumsView(QWidget* parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(20, 0, 40, 0);
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

void ArtistAlbumsView::onArtistChanged(Artist* artist)
{
    QMutexLocker locker(&m_mutex);
    clearLayout(m_layout);

    if(artist)
    {
        m_artist = artist;
        QObject::connect(m_artist, SIGNAL(albumAdded(Album*)), this, SLOT(onAlbumAdded(Album*)));
        QObject::connect(m_artist, SIGNAL(albumUpdated(Album*, quint8)), this, SLOT(onAlbumUpdated(Album*, quint8)));
        QObject::connect(m_artist, SIGNAL(albumRemoved(Album*)), this, SLOT(onAlbumRemoved(Album*)));

        m_widgets.clear();
        m_lineWidgets.clear();

        for(quint8 i = 0; i < artist->albums().size(); i++)
        {
            ArtistAlbumWidget* widget = new ArtistAlbumWidget();
            widget->setAlbum(artist->albums().at(i));
            m_widgets.push_back(widget);
            m_layout->addWidget(widget);

            if(i != artist->albums().size() - 1)
            {
                LineWidget* lineWidget = new LineWidget(Qt::Horizontal);
                m_lineWidgets.push_back(lineWidget);
                m_layout->addWidget(lineWidget);
            }
        }
    }
}

void ArtistAlbumsView::onAlbumAdded(Album* album)
{
    if(album)
    {
        /* TODO: Add new album instead of repaint all of them
         *       Check for alphabetical order before adding it */
        onArtistChanged(album->artist());
    }
}

void ArtistAlbumsView::onAlbumUpdated(Album* album, quint8 fields)
{
    if(album)
    {
        m_widgets.at(widgetIndex(album))->setAlbum(album, fields);
    }
}

void ArtistAlbumsView::onAlbumRemoved(Album* album)
{
    if(album)
    {
        quint16 index = widgetIndex(album);
        m_widgets.takeAt(index)->deleteLater();
        delete m_lineWidgets.takeAt(index);
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
