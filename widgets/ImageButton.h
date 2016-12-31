#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QAbstractButton>

class ImageButton : public QAbstractButton
{
  Q_OBJECT

  public:
    explicit ImageButton(QWidget* parent = 0);

    void clear();
    void setPixmap(const QString& path);
    void setPixmap(const QPixmap& pixmap);
    void setPixmap(const QString& path, const QIcon::State state, QIcon::Mode mode = QIcon::Normal);
    void setPixmap(const QPixmap& pixmap, const QIcon::State state, QIcon::Mode mode = QIcon::Normal);

    virtual QSize sizeHint() const;

  protected:
    virtual void paintEvent(QPaintEvent* event);

  private:
    QSize m_sizeHint;
};

#endif // IMAGEBUTTON_H
