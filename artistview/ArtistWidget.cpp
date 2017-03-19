#include "ArtistWidget.h"

#include <QAction>
#include <QMenu>
#include <QPaintEvent>
#include <QPainter>

ArtistWidget::ArtistWidget(const Artist* artist, QWidget* parent) : ClickableWidget(parent), m_focussed(false)
{
    c_artist = artist;

    m_cover = new QLabel();
    m_cover->setFixedWidth(ArtistWidget::IMAGE_WIDTH);

    if(c_artist->albums().size() > 0)
    {
        Album* album = c_artist->albums().at(0);

        if(!album || album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(ArtistWidget::IMAGE_WIDTH, ArtistWidget::IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(album->cover().scaled(ArtistWidget::IMAGE_WIDTH, ArtistWidget::IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }
    }

    m_artistName = new ElidedLabel(c_artist->name());
    m_artistName->setAlignment(Qt::AlignVCenter);
    m_artistName->setFixedHeight(ArtistWidget::WIDGET_HEIGHT);
    m_artistName->setStyleSheet(QString("color: white;"));

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(16);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_artistName);

    setContextMenuPolicy(Qt::CustomContextMenu);
    setMaximumSize(ArtistWidget::WIDGET_WIDTH, ArtistWidget::WIDGET_HEIGHT);
    setLayout(m_layout);

    QObject::connect(this, SIGNAL(leftButtonClicked()), this, SLOT(onLeftButtonClicked()));
    QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenuRequested(QPoint)));
}

ArtistWidget::~ArtistWidget()
{
    //TODO
}

void ArtistWidget::focusIn()
{
    m_focussed = true;
    repaint();
}

void ArtistWidget::focusOut()
{
    m_focussed = false;
    repaint();
}

const Artist* ArtistWidget::artist() const
{
    return c_artist;
}

void ArtistWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(m_focussed)
    {
        painter.save();
        painter.setBrush(QColor(0, 0, 0, 10));
        painter.setPen(QColor(0, 0, 0, 10));
        painter.drawRect(event->rect());
        painter.restore();
        QWidget::paintEvent(event);
    }
    else
    {
        ClickableWidget::paintEvent(event);
    }
}

void ArtistWidget::onLeftButtonClicked()
{
    emit widgetClicked(this);
}

void ArtistWidget::onContextMenuRequested(QPoint pos)
{
    QMenu* menu = new QMenu();

    QAction removeAction("Remove", this);
    QObject::connect(&removeAction, &QAction::triggered, [=] () { emit removeArtistWidgetClicked(this); });
    menu->addAction(&removeAction);

    menu->exec(mapToGlobal(pos));
}
