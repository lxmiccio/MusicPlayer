#include "ArtistWidget.h"

ArtistWidget::ArtistWidget(const Artist* artist, QWidget* parent) : QWidget(parent)
{
    c_artist = artist;

    m_cover = new ClickableLabel();
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

    setMaximumSize(ArtistWidget::WIDGET_WIDTH, ArtistWidget::WIDGET_HEIGHT);
    setLayout(m_layout);

    QObject::connect(m_cover, SIGNAL(clicked()), this, SLOT(onCoverClicked()));
    QObject::connect(m_artistName, SIGNAL(clicked()), this, SLOT(onCoverClicked()));
}


ArtistWidget::~ArtistWidget()
{
    //TODO
}

const Artist& ArtistWidget::artist() const
{
    return *c_artist;
}

void ArtistWidget::onCoverClicked()
{
    emit coverClicked(c_artist);
}
