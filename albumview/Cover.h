#ifndef COVER_H
#define COVER_H

#include <QFuture>
#include <QFutureWatcher>
#include <QVBoxLayout>

#include "Album.h"
#include "ClickableLabel.h"
#include "ElidedLabel.h"

class Cover : public QWidget
{
    Q_OBJECT

    public:
        explicit Cover(const Album* album, QWidget* parent = 0);
        ~Cover();

        const Album& album() const;

        static const quint16 COVER_HEIGHT = 215;
        static const quint16 COVER_WIDTH = 175;

        static const quint16 IMAGE_HEIGHT = 175;
        static const quint16 IMAGE_WIDTH = 175;

    signals:
        void coverClicked(const Album& album);

    private slots:
        void onCoverClicked();

    private:
        const Album* c_album;

        ClickableLabel* m_cover;
        ElidedLabel* m_albumTitle;
        ElidedLabel* m_artistName;
        QVBoxLayout* m_layout;
};

#endif // COVER_H
