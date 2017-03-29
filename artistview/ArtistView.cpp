#include "ArtistView.h"

ArtistView::ArtistView(QWidget* parent) : QWidget(parent)
{
    m_selectedArtistWidget = NULL;

    m_lowerSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_upperSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_middleVerticalSpacer = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_trackLoader = new TrackLoader();

    m_leftLayout = new QVBoxLayout();
    m_leftLayout->addItem(m_upperSpacer);
    m_leftLayout->addItem(m_lowerSpacer);
    ScrollableArea* m_leftLayoutScrollable = new ScrollableArea();
    QWidget* widget = new QWidget();
    widget->setLayout(m_leftLayout);
    m_leftLayoutScrollable->setWidget(widget);
    QObject::connect(m_leftLayoutScrollable, SIGNAL(filesDropped(QVector<QFileInfo>)), m_trackLoader, SLOT(loadTracks(QVector<QFileInfo>)));

    m_albumView = new ArtistAlbumsView();
    m_albumViewScrollable = new ScrollableArea();
    m_albumViewScrollable->setWidget(m_albumView);
    m_albumViewScrollable->hide();
    QObject::connect(this, SIGNAL(coverClicked(const Artist*)), m_albumView, SLOT(onArtistChanged(const Artist*)));

    m_splitter = new QSplitter();
    m_splitter->setHandleWidth(3);
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
    delete m_trackLoader;
    clearLayout(m_leftLayout);
    clearLayout(m_layout);
}

/* To improve performance the widgets into the given layout aren't deleted
 * Because of that, before calling clearLayout, be sure to delete the widget that hasn't to be shown */
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
    qSort(m_artists.begin(), m_artists.end(), [] (const Artist* artist1, const Artist* artist2) -> bool {
        return artist1->name() < artist2->name();
    });

    qSort(m_artistWidgets.begin(), m_artistWidgets.end(), [] (const ArtistWidget* artistWidget1, const ArtistWidget* artistWidget2) -> bool {
        return artistWidget1->artist()->name() < artistWidget2->artist()->name();
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

void ArtistView::repaintCoversAfterWidgetRemoved()
{
    QMutexLocker locker(&m_mutex);

    clearLayout(m_leftLayout);
    m_leftLayout->addItem(m_upperSpacer);
    m_leftLayout->addItem(m_lowerSpacer);

    foreach(ArtistWidget* i_artistWidget, m_artistWidgets)
    {
        m_leftLayout->insertWidget(m_leftLayout->count() - 2, i_artistWidget);
        m_leftLayout->insertItem(m_leftLayout->count() - 2, m_middleVerticalSpacer);
    }
}

void ArtistView::onAlbumAdded(const Album* album)
{
    if(album && album->artist())
    {
        QMutexLocker locker(&m_mutex);

        m_albumViewScrollable->show();

        if(!m_artists.contains(album->artist()))
        {
            Artist* artist = album->artist();
            m_artists.push_back(artist);

            ArtistWidget* artistWidget = new ArtistWidget(artist);
            m_artistWidgets.push_back(artistWidget);
            QObject::connect(artistWidget, SIGNAL(widgetClicked(ArtistWidget*)), this, SLOT(onArtistWidgetClicked(ArtistWidget*)));
            QObject::connect(artistWidget, SIGNAL(removeArtistWidgetClicked(ArtistWidget*)), this, SLOT(onRemoveArtistWidgetClicked(ArtistWidget*)));

            repaintCovers();
        }
    }
}

void ArtistView::onArtistWidgetClicked(ArtistWidget* widget)
{
    if(widget != m_selectedArtistWidget)
    {
        if(m_selectedArtistWidget)
        {
            m_selectedArtistWidget->focusOut();
        }

        m_selectedArtistWidget = widget;
        widget->focusIn();
    }

    emit coverClicked(widget->artist());
}

void ArtistView::onRemoveArtistWidgetClicked(ArtistWidget* widget)
{
    if(widget)
    {
        qint16 index = m_artistWidgets.indexOf(widget);
        bool updateAlbumView = widget->artist() == m_albumView->artist();

        m_artists.removeOne(const_cast<Artist*>(widget->artist()));
        m_artistWidgets.removeOne(widget);
        widget->deleteLater();

        if(updateAlbumView)
        {
            if(index == 0 && !m_artistWidgets.isEmpty())
            {
                m_albumView->onArtistChanged(m_artists.first());
            }
            else if(index == 0 && m_artistWidgets.isEmpty())
            {
                m_albumView->onArtistChanged(NULL);
                m_albumViewScrollable->hide();
            }
            else if(index >= m_artistWidgets.size())
            {
                m_albumView->onArtistChanged(m_artists.last());
            }
            else
            {
                m_albumView->onArtistChanged(m_artists.at(index));
            }
        }

        repaintCoversAfterWidgetRemoved();

        //TODO: Stop the track if it belonged to the deleted artist?
    }
}
