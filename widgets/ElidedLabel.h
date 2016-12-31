#ifndef ELIDEDLABEL_H
#define ELIDEDLABEL_H

#include <QFrame>
#include <QTime>

class ElidedLabel : public QFrame
{
  Q_OBJECT

  public:
    explicit ElidedLabel(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    explicit ElidedLabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags flags = 0);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

    Qt::TextElideMode elideMode() const;
    void setElideMode(Qt::TextElideMode elideMode);

    void setFont(const QFont& font);

    int margin() const;
    void setMargin(int margin);

    QString text() const;
    void setText(const QString& text);

    bool wordWrap();
    void setWordWrap(bool wordWrap);

    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

  public slots:
    //void setWordWrap(bool wordWrap);

  signals:
    void clicked();
    void textChanged(const QString& text);

  protected:
    virtual void changeEvent(QEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);

  private:
    QString m_text;

    Qt::Alignment m_alignment;
    Qt::TextElideMode m_elideMode;

    QTime m_time;

    int m_margin;
    bool m_wordWrap;
};

#endif // ELIDEDLABEL_H
