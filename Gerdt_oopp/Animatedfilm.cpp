#include "AnimatedFilm.h"

BOOST_CLASS_EXPORT(AnimatedFilm)
BOOST_CLASS_VERSION(AnimatedFilm, 1)

void AnimatedFilm::draw(QPainter &painter, int x, int y, const QVector<int>& columnWidth) const {
    films::draw(painter, x, y, columnWidth);
    int rowHeight = 20;

    // Рисуем дополнительные поля для AnimatedFilm
    painter.drawText(x + 6 * columnWidth[0], y, columnWidth[0], rowHeight, Qt::AlignCenter, QString::fromStdString(voice_actors));
    painter.drawText(x + 6 * columnWidth[0], y + rowHeight, columnWidth[0], rowHeight, Qt::AlignCenter, QString::fromStdString(animation_style));
}

QSize AnimatedFilm::textBlockSize(QPainter &painter) const {
    QSize baseSize = films::textBlockSize(painter);
    int additionalHeight = 20;
    return QSize(baseSize.width(), baseSize.height() + additionalHeight);
}
