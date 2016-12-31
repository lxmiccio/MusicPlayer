#include "ElidedLabel.h"

#include <QApplication>
#include <QPainter>
#include <QTextLayout>
#include <QTextLine>

ElidedLabel::ElidedLabel(QWidget* parent, Qt::WindowFlags flags) : QFrame(parent, flags)
{
  m_text = QString();

  m_alignment = Qt::AlignLeft;
  m_elideMode = Qt::ElideRight;
  m_margin = 0;
  m_wordWrap = false;

  setContentsMargins(0, 0, 0, 0);
}

ElidedLabel::ElidedLabel(const QString& text, QWidget* parent, Qt::WindowFlags flags) : QFrame(parent, flags)
{
  m_text = text;

  m_alignment = Qt::AlignLeft;
  m_elideMode = Qt::ElideRight;
  m_margin = 0;
  m_wordWrap = false;

  setContentsMargins(0, 0, 0, 0);
}

Qt::Alignment ElidedLabel::alignment() const
{
  return m_alignment;
}

void ElidedLabel::setAlignment(Qt::Alignment alignment)
{
  if(m_alignment != alignment) {
    m_alignment = alignment;

    update();
  }
}

Qt::TextElideMode ElidedLabel::elideMode() const
{
  return m_elideMode;
}

void ElidedLabel::setElideMode(Qt::TextElideMode elideMode)
{
  if(m_elideMode != elideMode) {
    m_elideMode = elideMode;

    updateGeometry();
    update();
  }
}

void ElidedLabel::setFont(const QFont& font)
{
  QWidget::setFont(font);

  updateGeometry();
  update();
}

int ElidedLabel::margin() const
{
  return m_margin;
}

void ElidedLabel::setMargin(int margin)
{
  m_margin = margin;
}

QString ElidedLabel::text() const
{
  return m_text;
}

void ElidedLabel::setText(const QString& text)
{
  if(m_text != text) {
    m_text = text;

    updateGeometry();
    update();

    emit textChanged(text);
  }
}

bool ElidedLabel::wordWrap()
{
  return m_wordWrap;
}

void ElidedLabel::setWordWrap(bool wordWrap)
{
  m_wordWrap = wordWrap;

  repaint();
}

QSize ElidedLabel::sizeHint() const
{
  const QFontMetrics& metrics = this->fontMetrics();
  return QSize(metrics.width(m_text) + m_margin * 2, metrics.height() + m_margin * 2);
}

QSize ElidedLabel::minimumSizeHint() const
{
  switch(m_elideMode)
  {
    case Qt::ElideNone: {
      return sizeHint();
    }

    default: {
      const QFontMetrics& metrics = this->fontMetrics();
      return QSize(metrics.width("..."), metrics.height());
    }
  }
}

void ElidedLabel::changeEvent(QEvent* event)
{
  QFrame::changeEvent(event);

  switch(event->type())
  {
    case QEvent::ApplicationFontChange:
    case QEvent::FontChange: {
      updateGeometry();
      update();
      break;
    }

    default:
      break;
    }
}

void ElidedLabel::mousePressEvent(QMouseEvent* event)
{
  QFrame::mousePressEvent(event);
  this->m_time.start();
}

void ElidedLabel::mouseReleaseEvent(QMouseEvent* event)
{
  QFrame::mouseReleaseEvent(event);

  if(m_time.elapsed() < qApp->doubleClickInterval()) {
    emit clicked();
  }
}

void ElidedLabel::paintEvent(QPaintEvent* event)
{
  QFrame::paintEvent(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::TextAntialiasing);

  QRect rect = contentsRect();
  rect.adjust(m_margin, m_margin, -m_margin, -m_margin);

  if(m_wordWrap) {
    QTextLayout textLayout(m_text);
    textLayout.setFont(painter.font());

    int lineCount = 0;
    int lineLimit = rect.height() / fontMetrics().height();

    int widthUsed = 0;

    textLayout.beginLayout();

    while(++lineCount < lineLimit) {
      QTextLine line = textLayout.createLine();

      if(!line.isValid()) {
        break;
      }

      line.setLineWidth(rect.width());
      widthUsed += line.naturalTextWidth();
      this->setMinimumHeight(300);
    }


    textLayout.endLayout();
    widthUsed += rect.width();

    const QString elidedText = this->fontMetrics().elidedText(m_text, Qt::ElideRight, widthUsed);
    painter.drawText(rect, m_alignment | Qt::TextWordWrap, elidedText);
  } else {
    const QString elidedText = this->fontMetrics().elidedText(m_text, m_elideMode, rect.width());
    painter.drawText(rect, m_alignment, elidedText);
  }
}
