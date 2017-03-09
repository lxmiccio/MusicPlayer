#include "ListArtistView.h"

ListArtistView::ListArtistView(QWidget* parent) : QWidget(parent)
{
    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_upperSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_middleVerticalSpacer = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_albumView = new ArtistAlbumsView();
    QObject::connect(this, SIGNAL(coverClicked(const Artist*)), m_albumView, SLOT(onArtistChanged(const Artist*)));

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->addItem(m_upperSpacer);
    m_leftLayout->addItem(m_lowerSpacer);

    m_layout = new QSplitter();
    m_layout->setContentsMargins(40, 16, 40, 12);
    QWidget* widget = new QWidget();
    widget->setLayout(m_leftLayout);
    m_layout->addWidget(widget);
    m_layout->addWidget(m_albumView);

    m_mainL = new QVBoxLayout();
    m_mainL->addWidget(m_layout);
    this->setLayout(m_mainL);

    MusicLibrary* musicLibrary = MusicLibrary::instance();
    QObject::connect(musicLibrary, SIGNAL(albumAdded(const Album*)), this, SLOT(onAlbumAdded(const Album*)));
}

ListArtistView::~ListArtistView()
{
    //TODO
}

void ListArtistView::onScrollAreaResized(QResizeEvent* event)
{
    //TODO
}

void ListArtistView::clearLayout(QLayout* layout)
{
    //TODO
}

void ListArtistView::repaintCovers()
{
    //TODO
}

void ListArtistView::onAlbumAdded(const Album* album)
{
    if(album && album->artist())
    {
        QMutexLocker locker(&m_mutex);

        if(!m_artists.contains(album->artist()))
        {
            Artist* artist = album->artist();
            m_artists.push_back(artist);

            ArtistWidget* artistWidget = new ArtistWidget(artist);
            m_artistWidgets.push_back(artistWidget);
            QObject::connect(artistWidget, SIGNAL(coverClicked(const Artist*)), this, SLOT(onCoverClicked(const Artist*)));

            qSort(m_artists.begin(), m_artists.end(), [] (const Artist* artist1, const Artist* artist2) -> bool {
                    return artist1->name() < artist2->name();
            });

            qSort(m_artistWidgets.begin(), m_artistWidgets.end(), [] (const ArtistWidget* artistWidget1, const ArtistWidget* artistWidget2) -> bool {
                    return artistWidget1->artist().name() < artistWidget2->artist().name();
            });

            m_leftLayout->insertWidget(m_leftLayout->count() - 2, artistWidget);
            m_leftLayout->insertItem(m_leftLayout->count() - 2, m_middleVerticalSpacer);
        }
    }
}

void ListArtistView::onCoverClicked(const Artist* artist)
{
    emit coverClicked(artist);
}
