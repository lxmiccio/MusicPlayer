#ifndef ARTISTALBUMWIDGET_H
#define ARTISTALBUMWIDGET_H

#include <QApplication>
#include <QFont>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "Album.h"
#include "ElidedLabel.h"
#include "Playlist.h"
#include "TracksListView.h"

class ArtistAlbumWidget : public QWidget
{
        Q_OBJECT

    public:
        ArtistAlbumWidget(QWidget* parent = 0);
        ~ArtistAlbumWidget();

        Album* album() const;
        void setAlbum(Album* album, quint8 fields = UINT8_MAX);

        static const quint16 IMAGE_HEIGHT = 100;
        static const quint16 IMAGE_WIDTH = 100;

    signals:
        void playlistSelected(Playlist* playlist);

    private slots:
        void onAlbumUpdated(Album* album, quint8 fields);
        void onDoubleClicked(const QModelIndex& index);

    private:
        void clear();

        Album* m_album;
        QLabel* m_cover;
        ElidedLabel* m_albumTitle;

        TracksListView* m_tracksListView;

        QSpacerItem* m_leftLayoutUpperSpacer;
        QSpacerItem* m_leftLayoutMiddleSpacer;
        QSpacerItem* m_leftLayoutLowerSpacer;
        QSpacerItem* m_rightLayoutMiddleSpacer;

        QHBoxLayout* m_layout;
        QVBoxLayout* m_leftLayout;
        QVBoxLayout* m_rightLayout;

#ifdef LOWER_ALIGNMENT
        QVBoxLayout* m_layout;
        QHBoxLayout* m_upperLayout;
        QHBoxLayout* m_lowerLayout;

        QSpacerItem* m_upperLayoutLeftSpacer;
        QSpacerItem* m_upperLayoutRightSpacer;
        QSpacerItem* m_middleSpacer;
        QSpacerItem* m_lowerLayoutLeftSpacer;
        QSpacerItem* m_lowerSpacer;
#endif
};

#endif// ARTISTALBUMWIDGET_H
