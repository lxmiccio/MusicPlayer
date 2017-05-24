#include "ArtistWidget.h"

ArtistWidget::ArtistWidget(Artist* artist, QWidget* parent) : ClickableWidget(parent), m_focussed(false)
{
    m_artist = artist;

    m_cover = new QLabel();
    m_cover->setFixedWidth(ArtistWidget::IMAGE_WIDTH);

    if(m_artist->albums().size() > 0)
    {
        Album* album = m_artist->albums().at(0);

        if(!album || album->cover().isNull())
        {
            m_cover->setPixmap(QPixmap::fromImage(QImage(":/images/album-placeholder.png")).scaled(ArtistWidget::IMAGE_WIDTH,
                                                                                                   ArtistWidget::IMAGE_HEIGHT,
                                                                                                   Qt::KeepAspectRatio,
                                                                                                   Qt::SmoothTransformation));
        }
        else
        {
            m_cover->setPixmap(QPixmap(album->cover().scaled(ArtistWidget::IMAGE_WIDTH,
                                                             ArtistWidget::IMAGE_HEIGHT,
                                                             Qt::KeepAspectRatio,
                                                             Qt::SmoothTransformation)));
        }
    }

    m_artistName = new ElidedLabel(m_artist->name());
    m_artistName->setAlignment(Qt::AlignVCenter);
    m_artistName->setFixedHeight(ArtistWidget::WIDGET_HEIGHT);
    m_artistName->setStyleSheet("color: white;");

    m_layout = new QHBoxLayout();
    m_layout->setMargin(0);
    m_layout->setSpacing(16);
    m_layout->addWidget(m_cover);
    m_layout->addWidget(m_artistName);

    setContextMenuPolicy(Qt::CustomContextMenu);
    setLayout(m_layout);
    setMaximumSize(ArtistWidget::WIDGET_WIDTH, ArtistWidget::WIDGET_HEIGHT);

    QObject::connect(this, SIGNAL(leftButtonClicked()), this, SLOT(onLeftButtonClicked()));
    QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenuRequested(QPoint)));
}

ArtistWidget::~ArtistWidget()
{
    //TODO
}

Artist* ArtistWidget::artist() const
{
    return m_artist;
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

void ArtistWidget::paintEvent(QPaintEvent* event)
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

void ArtistWidget::onContextMenuRequested(QPoint position)
{
    QMenu* menu = new QMenu();

    QAction removeAction("Remove", this);
    QObject::connect(&removeAction, &QAction::triggered, [=] () { emit removeArtistWidgetClicked(this); });
    menu->addAction(&removeAction);

    menu->exec(mapToGlobal(position));
}

void ArtistWidget::onLeftButtonClicked()
{
    emit widgetClicked(this);
}
