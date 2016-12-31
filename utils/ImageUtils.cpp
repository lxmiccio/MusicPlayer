#include "ImageUtils.h"

#include <QPainter>
#include <QSvgRenderer>

QPixmap ImageUtils::pixmap(const QString& image, const QSize& size, double opacity, QColor color)
{
  if(size.height() < 0 || size.width() < 0) {
    return QPixmap();
  }

  QPixmap pixmap;

  if(image.endsWith(QString(".svg"), Qt::CaseInsensitive)) {
    QSvgRenderer svgRenderer(image);

    pixmap = QPixmap(size.height() == 0 || size.width() == 0 ? svgRenderer.defaultSize() : size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setOpacity(opacity);
    svgRenderer.render(&painter);
    painter.end();

    if(color.alpha() > 0) {
      pixmap = ImageUtils::tint(pixmap, color);
    }
  } else {
    pixmap = QPixmap(image);
  }

  if(not pixmap.isNull() and not size.isNull() and pixmap.size() != size) {
    if(size.height() == 0) {
      pixmap = pixmap.scaledToWidth(size.width(), Qt::SmoothTransformation);
    } else if(size.width() == 0) {
      pixmap = pixmap.scaledToHeight(size.height(), Qt::SmoothTransformation);
    } else {
      pixmap = pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
  }

  return pixmap;
}

QImage ImageUtils::blur(const QImage &image, const QRect &rect, int radius, bool alphaOnly, bool blackWhite)
{
  int tab[] = {14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2};
  int alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius-1];

  QImage result = image.convertToFormat(QImage::Format_ARGB32);

  if(blackWhite) {
    for(int i = 0; i < result.width(); ++i) {
      for(int j = 0; j < result.height(); ++j) {
        const QRgb color = result.pixel(i, j);
        const int gray = qGray(color);
        result.setPixel(i, j, qRgb(gray*0.3, gray*0.3, gray*0.3));
      }
    }
  }

  int r1 = rect.top();
  int r2 = rect.bottom();
  int c1 = rect.left();
  int c2 = rect.right();

  int bpl = result.bytesPerLine();
  int rgba[4];

  unsigned char* p;

  int i1 = 0;
  int i2 = 3;

  if(alphaOnly) {
    i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);
  }

  for(int col = c1; col <= c2; col++) {
    p = result.scanLine(r1) + col * 4;

    for(int i = i1; i <= i2; i++) {
      rgba[i] = p[i] << 4;
    }

    p += bpl;

    for(int j = r1; j < r2; j++, p += bpl) {
      for(int i = i1; i <= i2; i++) {
        p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
      }
    }
  }

  for(int row = r1; row <= r2; row++) {
    p = result.scanLine(row) + c1 * 4;

    for(int i = i1; i <= i2; i++) {
      rgba[i] = p[i] << 4;
    }

    p += 4;

    for(int j = c1; j < c2; j++, p += 4) {
      for(int i = i1; i <= i2; i++) {
        p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
      }
    }
  }

  for(int col = c1; col <= c2; col++) {
    p = result.scanLine(r2) + col * 4;

    for(int i = i1; i <= i2; i++) {
      rgba[i] = p[i] << 4;
    }

    p -= bpl;

    for(int j = r1; j < r2; j++, p -= bpl) {
      for(int i = i1; i <= i2; i++) {
        p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
      }
    }
  }

  for(int row = r1; row <= r2; row++) {
    p = result.scanLine(row) + c2 * 4;

    for(int i = i1; i <= i2; i++) {
      rgba[i] = p[i] << 4;
    }

    p -= 4;
    for(int j = c1; j < c2; j++, p -= 4) {
      for(int i = i1; i <= i2; i++) {
        p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
      }
    }
  }

  return result;
}

QPixmap ImageUtils::tint(const QPixmap &pixmap, const QColor &color)
{
  QImage image(pixmap.size(), QImage::Format_ARGB32);

  QPainter painter(&image);
  painter.drawPixmap(0, 0, pixmap);
  painter.fillRect(image.rect(), color);
  painter.setCompositionMode(QPainter::CompositionMode_Screen);
  painter.end();

  image.setAlphaChannel(pixmap.toImage().alphaChannel());

  return QPixmap::fromImage(image);
}

QPixmap ImageUtils::stringToImage(QImage image, const QString &string)
{
  QPainter painter(&image);
  painter.setPen(QPen(QColor(0,0,0)));
  painter.setFont(QFont("Times", 12, QFont::Bold));
  painter.drawText(image.rect(), Qt::AlignCenter, string);

  return QPixmap::fromImage(image);
}
