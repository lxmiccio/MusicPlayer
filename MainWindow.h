#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        static MainWindow* instance();

    protected:
        explicit MainWindow(QWidget* parent = 0);

    private slots:
        void onPlaylistsChanged();

    private:
        static MainWindow* m_instance;

        QStackedWidget* m_stackedWidget;

        QAction* m_showArtistView;
        QAction* m_showAlbumView;
        QAction* m_showTrackView;
        QMenu* m_playlistMenu;
        QVector<QAction*> m_playlistsView;
        QMenu* m_viewsMenu;
        QMenuBar* m_menuBar;
};

#endif// MAINWINDOW_H
