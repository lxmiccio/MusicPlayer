//#include "AlbumTableItem.h"


//AlbumTableItem::AlbumTableItem(Album *album, QWidget *parent, Qt::WindowFlags flags, int type) : QWidget(parent), QTableWidgetItem(type)
//{

//    m_albumCoverWidget = new AlbumCoverWidget(album);
//    QObject::connect(m_albumCoverWidget, SIGNAL(coverClicked(Album*)), this, SIGNAL(coverClicked(Album*)));

//    m_topSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
//    m_rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
//    m_bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
//    m_leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

//    m_verticalLayout = new QVBoxLayout();
//    m_verticalLayout->setMargin(0);
//    m_verticalLayout->addItem(m_topSpacer);
//    m_verticalLayout->addWidget(m_albumCoverWidget);
//    m_verticalLayout->addItem(m_bottomSpacer);

//    m_layout = new QHBoxLayout();
//    m_layout->setMargin(0);
//    m_layout->addItem(m_leftSpacer);
//    m_layout->addLayout(m_verticalLayout);
//    m_layout->addItem(m_rightSpacer);

//    setLayout(m_layout);
//    setFixedWidth(300);
//    setFixedHeight(300);
//}


//Album* AlbumTableItem::album() const
//{
//    return m_albumCoverWidget->album();
//}

//void AlbumTableItem::setAlbum(Album* album)
//{
//    if(album)
//    {
//        m_albumCoverWidget->setAlbum(album);
//    }
//}

//quint8 AlbumTableItem::position()
//{
//    return m_position;
//}

//void AlbumTableItem::setPosition(quint8 position)
//{
//    if(position != m_position)
//    {
//        m_position = position;
//        m_margin -= 1;
//        setMargin(m_margin + 1);
//    }
//}

//quint8 AlbumTableItem::margin()
//{
//    return m_margin;
//}

//void AlbumTableItem::setMargin(quint8 margin)
//{
//    if(margin != m_margin)
//    {
//        m_margin = margin;

////        quint8 marginTop = (m_position & TOP) ? 0 : 10;
////        quint8 marginRight = (m_position & RIGHT) ? 0 : margin;
////        quint8 marginBottom = (m_position & BOTTOM) ? 0 : 10;
////        quint8 marginLeft = (m_position & LEFT) ? 0 : margin;

////        m_topSpacer->changeSize(0, marginTop, QSizePolicy::Fixed, QSizePolicy::Fixed);
////        m_rightSpacer->changeSize(marginRight, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
////        m_bottomSpacer->changeSize(0, marginBottom, QSizePolicy::Fixed, QSizePolicy::Fixed);
////        m_leftSpacer->changeSize(marginLeft, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
//    }
//}
