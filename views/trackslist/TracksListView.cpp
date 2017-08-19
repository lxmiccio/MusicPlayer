#include "TracksListView.h"

#include <QCommonStyle>
#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>
#include <QScrollBar>

#include "AudioEngine.h"
#include "GuiUtils.h"
#include "MusicLibrary.h"

TracksListView::TracksListView(quint8 mode, bool sort, QWidget* parent) : QTableView(parent)
{
    m_mode = mode;

    m_tracksListModel = new TracksListModel(sort);
    setModel(m_tracksListModel);

    m_tracksListDelegate = new TracksListDelegate(this);
    setItemDelegate(m_tracksListDelegate);

    horizontalHeader()->hide();
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setShowGrid(false);

    setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onContextMenuRequested(QPoint)));

    setStyleSheet(QString("QTableView {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"
                          "QTableView > QWidget > QWidget {"
                          "background: transparent;"
                          "border: 0px;"
                          "}"));

    verticalScrollBar()->setStyle(new QCommonStyle());
    verticalScrollBar()->setStyleSheet(GuiUtils::SCROLL_BAR_STYLE);

    QObject::connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onItemClicked(QModelIndex)));
    QObject::connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
    QObject::connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onItemDoubleClicked(QModelIndex)));

    QObject::connect(selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(onCurrentRowChanged(QModelIndex, QModelIndex)));
}

TracksListView::~TracksListView()
{

}

QSize TracksListView::fittingSize()
{
    return sizeHint();
}

quint8 TracksListView::mode() const
{
    return m_mode;
}

TracksListModel* TracksListView::tracksListModel() const
{
    return m_tracksListModel;
}

int TracksListView::rowCount() const
{
    return m_tracksListModel->rowCount();
}

int TracksListView::columnCount() const
{
    return m_tracksListModel->columnCount();
}

void TracksListView::propendItem(Track* track)
{
    m_tracksListModel->propendItem(track);
}

void TracksListView::appendItem(Track* track)
{
    m_tracksListModel->appendItem(track);
}

void TracksListView::removeItem(Track* track)
{
    m_tracksListModel->removeItem(track);
}

void TracksListView::insertItemAt(Track* track, int row)
{
    m_tracksListModel->insertItemAt(track, row);
}

void TracksListView::removeFirstItem()
{
    m_tracksListModel->removeFirstItem();
}

void TracksListView::removeLastItem()
{
    m_tracksListModel->removeLastItem();
}

void TracksListView::removeItemAt(int row)
{
    m_tracksListModel->removeItemAt(row);
}

void TracksListView::clear()
{
    m_tracksListModel->clear();
}

void TracksListView::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width() - TracksListView::TRACK_WIDTH - TracksListView::DURATION_WIDTH;

    if(m_mode == TracksListView::FULL)
    {
        setColumnWidth(TracksListView::TRACK_INDEX, TracksListView::TRACK_WIDTH);
        setColumnWidth(TracksListView::TITLE_INDEX, width / 3);
        setColumnWidth(TracksListView::ALBUM_INDEX, width / 3);
        setColumnWidth(TracksListView::ARTIST_INDEX, width / 3);
        setColumnWidth(TracksListView::DURATION_INDEX, TracksListView::DURATION_WIDTH);
    }
    else
    {
        setColumnWidth(TracksListView::TRACK_INDEX, TracksListView::TRACK_WIDTH);
        setColumnWidth(TracksListView::TITLE_INDEX, width);
        setColumnWidth(TracksListView::DURATION_INDEX, TracksListView::DURATION_WIDTH);

        setColumnHidden(TracksListView::ALBUM_INDEX, true);
        setColumnHidden(TracksListView::ARTIST_INDEX, true);
    }

    QTableView::resizeEvent(event);
}

QSize TracksListView::sizeHint()
{
    QSize hint = QTableView::sizeHint();

    if(model())
    {
        quint16 width = verticalHeader()->width() + 4;
        for(quint8 i = 0; i < model()->columnCount(); ++i)
        {
            width += columnWidth(i);
        }

        quint16 height = horizontalHeader()->height() + 4;
        for(quint8 i = 0; i < model()->rowCount(); ++i)
        {
            height += rowHeight(i);
        }

        hint.setWidth(width);
        hint.setHeight(height);
    }

    return hint;
}

void TracksListView::onContextMenuRequested(QPoint position)
{
    QMenu menu(this);

    QAction* changeArtist = menu.addAction("Change artist");
    QAction* changeAlbum = menu.addAction("Change album");
    QAction* changeTitle = menu.addAction("Change title");
    QAction* removeTrack = menu.addAction("Remove track");
    QAction* downloadCover = menu.addAction("Download cover");
    QAction* downloadLyrics = menu.addAction("Download lyrics");

    QMenu playlistMenu("Add to playlist");
    QAction* addPlaylist = playlistMenu.addAction("Create new");
    playlistMenu.addSeparator();

    QVector<QAction*> playlists;
    QStringList playlistsName = PlaylistManager::instance()->playlistsName();
    for(quint16 i = 0; i < playlistsName.size(); ++i)
    {
        playlists.append(playlistMenu.addAction(playlistsName.at(i)));
    }

    menu.addMenu(&playlistMenu);

    QMenu tempoMenu("Change tempo");
    QAction* x25 = tempoMenu.addAction("25%");
    QAction* x50 = tempoMenu.addAction("50%");
    QAction* x75 = tempoMenu.addAction("75%");
    QAction* x100 = tempoMenu.addAction("100%");
    QAction* valueTempo = tempoMenu.addAction("Custom value");
    menu.addMenu(&tempoMenu);

    QAction* selectedAction = menu.exec(viewport()->mapToGlobal(position));

    if(selectedAction == changeArtist)
    {
#if 0
        QString newArtist = QInputDialog::getText(0, "Track editing", "Artist:");
        Artist* artist = MusicLibrary::instance()->album(newArtist);
        const_cast<Track*>(m_tracksListModel->rootItem()->child(indexAt(position).row())->track())->setTitle(newTitle);
#endif
    }
    else if(selectedAction == changeAlbum)
    {
#if 0
        QString newAlbum = QInputDialog::getText(0, "Track editing", "Album:");
        Album* album = MusicLibrary::instance()->album(newAlbum);
        if(!album)
        {
            //changedAlbum(oldTrack(track*), newAlbum(qstring));
        }
        const_cast<Track*>(m_tracksListModel->rootItem()->child(indexAt(position).row())->track())->setTitle(newTitle);
#endif
    }
    else if(selectedAction == changeTitle)
    {
        QString newTitle = QInputDialog::getText(0, "Track editing", "Title:", QLineEdit::Normal, m_tracksListModel->rootItem()->child(indexAt(position).row())->track()->title());
        m_tracksListModel->rootItem()->child(indexAt(position).row())->track()->setTitle(newTitle);
    }
    else if(selectedAction == removeTrack)
    {
        QModelIndexList selection = selectionModel()->selectedRows();
        while(!selection.isEmpty())
        {
            MusicLibrary::instance()->removeTrack(m_tracksListModel->rootItem()->child(selection.takeLast().row())->track());
        }
    }
    else if(selectedAction == downloadCover)
    {
        QModelIndexList selection = selectionModel()->selectedRows();
        for(quint16 i = 0; i < selection.size(); ++i)
        {
            m_tracksListModel->rootItem()->child(selection.at(i).row())->track()->album()->downloadCover();
        }
    }
    else if(selectedAction == downloadLyrics)
    {
        QModelIndexList selection = selectionModel()->selectedRows();
        for(quint16 i = 0; i < selection.size(); ++i)
        {
            m_tracksListModel->rootItem()->child(selection.at(i).row())->track()->downloadLyrics();
        }
    }
    else if(selectedAction == x25 || selectedAction == x50 || selectedAction == x75 || selectedAction == x100 || selectedAction == valueTempo)
    {
        quint16 tempo = 0;

        if(selectedAction == x25)
        {
            tempo = 25;
        }
        else if(selectedAction == x50)
        {
            tempo = 50;
        }
        else if(selectedAction == x75)
        {
            tempo = 75;
        }
        else if(selectedAction == x100)
        {
            tempo = 100;
        }
        else if(selectedAction == valueTempo)
        {
            tempo = QInputDialog::getInt(0, "Change tempo", "Tempo(0-100):", 0, 0, 100);
        }

        QModelIndexList selection = selectionModel()->selectedRows();
        for(quint16 i = 0; i < selection.size(); ++i)
        {
            m_tracksListModel->rootItem()->child(selection.at(i).row())->track()->modifyTempo(tempo);
        }
    }
    else if(selectedAction == addPlaylist)
    {
        QString newPlaylist = QInputDialog::getText(0, "Create playlist", "Title:");

        Playlist* playlist = PlaylistManager::instance()->playlist(newPlaylist);
        if(!playlist)
        {
            playlist = new Playlist(newPlaylist);
        }

        QModelIndexList selection = selectionModel()->selectedRows();
        for(quint16 i = 0; i < selection.size(); ++i)
        {
            playlist->addTrack(m_tracksListModel->rootItem()->child(selection.at(i).row())->track());
        }

        PlaylistManager::instance()->savePlaylist(playlist);
    }
    else if(playlists.contains(selectedAction))
    {
        Playlist* playlist = PlaylistManager::instance()->playlist(playlists.at(playlists.indexOf(selectedAction))->text());
        if(playlist)
        {
            QModelIndexList selection = selectionModel()->selectedRows();
            for(quint16 i = 0; i < selection.size(); ++i)
            {
                playlist->addTrack(m_tracksListModel->rootItem()->child(selection.at(i).row())->track());
            }
        }

        PlaylistManager::instance()->savePlaylist(playlist);
    }
}

void TracksListView::onItemClicked(const QModelIndex& index)
{
    emit trackClicked(m_tracksListModel->rootItem()->child(index.row())->track());
}

void TracksListView::onItemEntered(const QModelIndex& index)
{
    emit trackEntered(m_tracksListModel->rootItem()->child(index.row())->track());
}

void TracksListView::onItemPressed(const QModelIndex& index)
{
    emit trackPressed(m_tracksListModel->rootItem()->child(index.row())->track());
}

void TracksListView::onItemDoubleClicked(const QModelIndex& index)
{
    Track* track = m_tracksListModel->rootItem()->child(index.row())->track();
    emit trackDoubleClicked(track);

    if(track && track->album())
    {
        QVector<Track*> tracks;
        for(quint8 i = index.row(); i < m_tracksListModel->rowCount(); ++i)
        {
            tracks.push_back(m_tracksListModel->rootItem()->child(i)->track());
        }

        Playlist* playlist = Playlist::fromTracks(tracks);
        AudioEngine::instance()->onPlaylistSelected(playlist);
    }
}

void TracksListView::onCurrentRowChanged(QModelIndex current, QModelIndex previous)
{
    Q_UNUSED(previous);

    if(current.row() >= 0)
    {
        emit trackSelected(m_tracksListModel->rootItem()->child(current.row())->track());
    }
}
