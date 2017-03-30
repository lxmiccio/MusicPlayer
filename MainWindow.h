#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        QStackedWidget* stackedWidget();

    public slots:
        void previousView();

    private:
        QStackedWidget* m_stackedWidget;

        QAction* showArtistView;
        QAction* showAlbumView;
        QMenuBar* m_menuBar;
        QMenu* m_viewsMenu;
};

#endif // MAINWINDOW_H
