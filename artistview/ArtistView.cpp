#include "ArtistView.h"

ArtistView::ArtistView(QWidget* parent) : QWidget(parent)
{
    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_upperSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_middleVerticalSpacer = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_trackLoader = new TrackLoader();

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->addItem(m_upperSpacer);
    m_leftLayout->addItem(m_lowerSpacer);
    ScrollableArea* m_leftLayoutScrollable = new ScrollableArea();
    m_leftLayoutScrollable->setLayout(m_leftLayout);
    QObject::connect(m_leftLayoutScrollable, SIGNAL(filesDropped(QVector<QFileInfo>)), m_trackLoader, SLOT(loadTracks(QVector<QFileInfo>)));

    m_albumView = new ArtistAlbumsView();
    m_albumViewScrollable = new ScrollableArea();
    m_albumViewScrollable->setWidget(m_albumView);
    QObject::connect(this, SIGNAL(coverClicked(const Artist*)), m_albumView, SLOT(onArtistChanged(const Artist*)));

    m_splitter = new QSplitter();
    m_splitter->setContentsMargins(40, 16, 40, 12);
    m_splitter->addWidget(m_leftLayoutScrollable);
    m_splitter->addWidget(m_albumViewScrollable);

    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_splitter);
    setLayout(m_layout);

    QObject::connect(MusicLibrary::instance(), SIGNAL(albumAdded(const Album*)), this, SLOT(onAlbumAdded(const Album*)));
}

ArtistView::~ArtistView()
{
    //TODO
}

void ArtistView::clearLayout(QLayout* layout)
{
    QLayoutItem* i_item;

    while((i_item = layout->takeAt(0)) != NULL)
    {
        if(i_item->layout())
        {
            clearLayout(i_item->layout());
            delete i_item->layout();
        }
    }
}

void ArtistView::repaintCovers()
{
    QMutexLocker locker(&m_mutex);

    QVector<Artist*> unsortedArtist;
    foreach(Artist* i_artist, m_artists)
    {
        unsortedArtist.push_back(i_artist);
    }

    qSort(m_artists.begin(), m_artists.end(), [] (const Artist* artist1, const Artist* artist2) -> bool {
        return artist1->name() < artist2->name();
    });

    bool repaint = false;
    for(quint16 i = 0; i < m_artists.size(); ++i)
    {
        if(m_artists.at(i) != unsortedArtist.at(i))
        {
            repaint = true;
            break;
        }
    }

    if(repaint)
    {
        qSort(m_artistWidgets.begin(), m_artistWidgets.end(), [] (const ArtistWidget* artistWidget1, const ArtistWidget* artistWidget2) -> bool {
            return artistWidget1->artist().name() < artistWidget2->artist().name();
        });

        clearLayout(m_leftLayout);
        m_leftLayout->addItem(m_upperSpacer);
        m_leftLayout->addItem(m_lowerSpacer);

        foreach(ArtistWidget* i_artistWidget, m_artistWidgets)
        {
            m_leftLayout->insertWidget(m_leftLayout->count() - 2, i_artistWidget);
            m_leftLayout->insertItem(m_leftLayout->count() - 2, m_middleVerticalSpacer);
        }
    }
}

void ArtistView::onAlbumAdded(const Album* album)
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

            m_leftLayout->insertWidget(m_leftLayout->count() - 2, artistWidget);
            m_leftLayout->insertItem(m_leftLayout->count() - 2, m_middleVerticalSpacer);
        }
    }
}

void ArtistView::onCoverClicked(const Artist* artist)
{
    emit coverClicked(artist);
}
