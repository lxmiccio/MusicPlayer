#include "TrackView.h"

#include "GuiUtils.h"
#include "MusicLibrary.h"

#include "LameWrapper.h"
#include "SoundTouchWrapper.h"

const quint8 TrackView::TRACK_INDEX;
const quint8 TrackView::TITLE_INDEX;
const quint8 TrackView::ALBUM_INDEX;
const quint8 TrackView::ARTIST_INDEX;
const quint8 TrackView::DURATION_INDEX;

TrackView::TrackView(quint8 mode, QWidget* parent) : QTableView(parent)
{
    m_mode = mode;

    m_soundTouch = new SoundTouchManager();

    m_trackModel = new TrackModel();

#if 0
    m_filterProxy = new TrackFilterProxy();
    m_filterProxy->setDynamicSortFilter(true);
    m_filterProxy->setSourceModel(m_trackModel);
    m_filterProxy->sort(0, Qt::AscendingOrder);
    QObject::connect(m_trackModel, SIGNAL(rowsInserted(QModelIndex, int, int)), m_filterProxy, SLOT(invalidate()));
    setModel(m_filterProxy);
#else
    setModel(m_trackModel);
#endif

    m_trackDelegate = new TrackDelegate(this);
    setItemDelegate(m_trackDelegate);

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

    QObject::connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onItemDoubleClicked(QModelIndex)));
}

TrackView::~TrackView()
{

}

QSize TrackView::fittingSize()
{
    return sizeHint();
}

quint8 TrackView::mode() const
{
    return m_mode;
}

TrackModel* TrackView::trackModel() const
{
    return m_trackModel;
}

int TrackView::rowCount() const
{
    return m_trackModel->rowCount();
}

int TrackView::columnCount() const
{
    return m_trackModel->columnCount();
}

void TrackView::propendItem(Track* track)
{
    m_trackModel->propendItem(track);
}

void TrackView::appendItem(Track* track)
{
    m_trackModel->appendItem(track);
}

void TrackView::removeItem(Track* track)
{
    m_trackModel->removeItem(track);
}

void TrackView::insertItemAt(Track* track, int row)
{
    m_trackModel->insertItemAt(track, row);
}

void TrackView::removeFirstItem()
{
    m_trackModel->removeFirstItem();
}

void TrackView::removeLastItem()
{
    m_trackModel->removeLastItem();
}

void TrackView::removeItemAt(int row)
{
    m_trackModel->removeItemAt(row);
}

void TrackView::clear()
{
    m_trackModel->clear();
}

void TrackView::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width() - TrackView::TRACK_WIDTH - TrackView::DURATION_WIDTH;

    if(m_mode == PlayingView::FULL)
    {
        setColumnWidth(TrackView::TRACK_INDEX, TrackView::TRACK_WIDTH);
        setColumnWidth(TrackView::TITLE_INDEX, width / 3);
        setColumnWidth(TrackView::ALBUM_INDEX, width / 3);
        setColumnWidth(TrackView::ARTIST_INDEX, width / 3);
        setColumnWidth(TrackView::DURATION_INDEX, TrackView::DURATION_WIDTH);
    }
    else
    {
        setColumnWidth(TrackView::TRACK_INDEX, TrackView::TRACK_WIDTH);
        setColumnWidth(TrackView::TITLE_INDEX, width);
        setColumnWidth(TrackView::DURATION_INDEX, TrackView::DURATION_WIDTH);

        setColumnHidden(TrackView::ALBUM_INDEX, true);
        setColumnHidden(TrackView::ARTIST_INDEX, true);
    }

    QTableView::resizeEvent(event);
}

QSize TrackView::sizeHint()
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

void TrackView::onContextMenuRequested(QPoint position)
{
    QMenu menu(this);

    QAction* changeArtist = menu.addAction("Change artist");
    QAction* changeAlbum = menu.addAction("Change album");
    QAction* changeTitle = menu.addAction("Change title");
    QAction* removeTrack = menu.addAction("Remove track");

    QAction* lyrics = menu.addAction("Lyrics");

    QMenu tempoMenu("Change tempo");

    QAction* x125 = tempoMenu.addAction("125%");
    QAction* x150 = tempoMenu.addAction("150%");
    QAction* x175 = tempoMenu.addAction("175%");
    QAction* x200 = tempoMenu.addAction("200%");

    menu.addMenu(&tempoMenu);



    QAction* selectedAction = menu.exec(viewport()->mapToGlobal(position));

    if(selectedAction == changeArtist)
    {
#if 0
        QString newArtist = QInputDialog::getText(0, "Track editing", "Artist:");
        Artist* artist = MusicLibrary::instance()->album(newArtist);
        const_cast<Track*>(m_trackModel->rootItem()->child(indexAt(position).row())->track())->setTitle(newTitle);
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
        const_cast<Track*>(m_trackModel->rootItem()->child(indexAt(position).row())->track())->setTitle(newTitle);
#endif
    }
    else if(selectedAction == changeTitle)
    {
        QString newTitle = QInputDialog::getText(0, "Track editing", "Title:");
        m_trackModel->rootItem()->child(indexAt(position).row())->track()->setTitle(newTitle);
    }
    else if(selectedAction == removeTrack)
    {
        QModelIndexList selection = selectionModel()->selectedRows();
        for(quint16 i = 0; i < selection.size(); ++i)
        {
            MusicLibrary::instance()->removeTrack(m_trackModel->rootItem()->child(selection.at(i).row())->track());
        }
    }
    else if(selectedAction == lyrics)
    {
        QString url_str = "http://api.musixmatch.com/ws/1.1/track.search";

        HttpRequestInput input(url_str, "GET");

        input.addParameter("apikey", "aeef299af4b395942213c77147c99ef8");
        input.addParameter("q_artist", m_trackModel->rootItem()->child(indexAt(position).row())->track()->artist()->name());
        input.addParameter("q_track", m_trackModel->rootItem()->child(indexAt(position).row())->track()->title());

        HttpRequestWorker* worker = new HttpRequestWorker(this);
        QObject::connect(worker, SIGNAL(on_execution_finished(HttpRequestWorker*)), this, SLOT(handle_result(HttpRequestWorker*)));
        worker->execute(&input);
    }
    else if(selectedAction == x125 || selectedAction == x150 || selectedAction == x175 || selectedAction == x200)
    {
        quint16 tempo = 0;

        if(selectedAction == x125)
        {
            tempo = 25;
        }
        else if(selectedAction == x150)
        {
            tempo = 50;
        }
        else if(selectedAction == x175)
        {
            tempo = 75;
        }
        else if(selectedAction == x200)
        {
            tempo = 100;
        }

        QVector<Track*> tracks;

        QModelIndexList selection = selectionModel()->selectedRows();
        for(quint16 i = 0; i < selection.size(); ++i)
        {
            tracks.push_back(m_trackModel->rootItem()->child(selection.at(i).row())->track());
        }

        m_soundTouch->changeTempo(tracks, tempo);
    }
}

void TrackView::onItemDoubleClicked(const QModelIndex& index)
{
    emit trackDoubleClicked(m_trackModel->rootItem()->child(index.row())->track());
}
