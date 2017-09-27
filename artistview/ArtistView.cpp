#include "ArtistView.h"

#include "MusicLibrary.h"

ArtistView::ArtistView(QWidget* parent) : QWidget(parent)
{
    m_artistsListView = new ArtistsListView();
    m_artistsListView->setFixedWidth(350);

    m_artistAlbumsView = new ArtistAlbumsView();
    QObject::connect(m_artistsListView, SIGNAL(artistSelected(Artist*)), m_artistAlbumsView, SLOT(onArtistChanged(Artist*)));

    m_scrollableWidget = new ScrollableWidget();
    m_scrollableWidget->setWidget(m_artistAlbumsView);

    m_splitter = new QSplitter();
    m_splitter->setContentsMargins(0, 0, 0, 0);
    m_splitter->setHandleWidth(3);
    m_splitter->addWidget(m_artistsListView);
    m_splitter->addWidget(m_scrollableWidget);

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(32);
    m_layout->addWidget(m_splitter);

    setLayout(m_layout);

    QObject::connect(MusicLibrary::instance(), SIGNAL(artistAdded(Artist*)), this, SLOT(onArtistAdded(Artist*)));
}

ArtistView::~ArtistView()
{

}

void ArtistView::onArtistAdded(Artist* artist)
{
    if(artist)
    {
        QObject::connect(artist, SIGNAL(destroyed(QObject*)), SLOT(onArtistDestroyed(QObject*)));
        m_artistsListView->appendItem(artist);
    }
}

void ArtistView::onArtistDestroyed(QObject* artist)
{
    //m_artistsListView->removeItem(static_cast<Artist*>(artist));
}
