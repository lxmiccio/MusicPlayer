//#ifndef ALBUMTABLEITEM_H
//#define ALBUMTABLEITEM_H

//#include <QLabel>
//#include <QVBoxLayout>
//#include <QHBoxLayout>
//#include <QSpacerItem>
//#include <QTableWidgetItem>
//#include <QVBoxLayout>
//#include <QWidget>
//#include <QTableWidgetItem>
//#include <QWidget>

//#include "AlbumCoverWidget.h"
//#include "Album.h"

//#define     WType      ((QTableWidgetItem::UserType)+200)


//class AlbumTableItem : public QTableWidgetItem, public QWidget
//{
//public:
//    AlbumTableItem(Album* album, QWidget* parent = 0, Qt::WindowFlags flags = 0, int type = WType);
////    QVariant data(int role) const
////    {

////        if (role==Qt::EditRole)
////            return m_albumCoverWidget->album()->title();
////        else if (role==Qt::CheckStateRole)
////            return Qt::Unchecked;
////        else if (role==Qt::DisplayRole)
////            return m_albumCoverWidget->album()->title();
////        else if (role==Qt::TextAlignmentRole)
////            return Qt::AlignRight;
////        else
////            return QTableWidgetItem::data(role);
////    }

//    Album* album() const;
//    void setAlbum(Album* album);

//    quint8 position();
//    void setPosition(quint8 position);

//    quint8 margin();
//    void setMargin(quint8 margin);

//signals:
//    void coverClicked(Album* album);

//private:
//    quint8 m_margin;
//    quint8 m_position;

//    AlbumCoverWidget* m_albumCoverWidget;

//    QSpacerItem* m_topSpacer;
//    QSpacerItem* m_rightSpacer;
//    QSpacerItem* m_bottomSpacer;
//    QSpacerItem* m_leftSpacer;

//    QVBoxLayout* m_verticalLayout;
//    QHBoxLayout* m_layout;
//};

//#endif // ALBUMTABLEITEM_H
