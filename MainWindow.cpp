#include "MainWindow.h"

#include "MainWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_stackedWidget = new QStackedWidget();
    setCentralWidget(m_stackedWidget);

    showArtistView = new QAction("ArtistView");
    showAlbumView = new QAction("AlbumView");

    m_viewsMenu = new QMenu("Views");
    m_viewsMenu->addAction(showArtistView);
    m_viewsMenu->addAction(showAlbumView);

    m_menuBar = new QMenuBar(this);
    m_menuBar->addMenu(m_viewsMenu);
    setMenuBar(m_menuBar);

    MainWidget* mainWidget = new MainWidget(this);
    m_stackedWidget->addWidget(mainWidget);
    QObject::connect(showArtistView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowArtistViewTriggered()));
    QObject::connect(showAlbumView, SIGNAL(triggered(bool)), mainWidget, SLOT(onShowAlbumViewTriggered()));
}

QStackedWidget* MainWindow::stackedWidget()
{
    return m_stackedWidget;
}

void MainWindow::previousView()
{
    QString currentClassName = m_stackedWidget->currentWidget()->metaObject()->className();

    for(qint8 i = m_stackedWidget->count() - 1; i >= 0; --i)
    {
        QWidget* widget = m_stackedWidget->widget(i);

        if(widget->metaObject()->className() == currentClassName)
        {
            m_stackedWidget->removeWidget(widget);
            delete widget;
        }
        else
        {
            m_stackedWidget->setCurrentWidget(m_stackedWidget->widget(i));
            break;
        }
    }
}
