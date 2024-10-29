#include "films.h"

void films::draw(QPainter &painter, int x, int y, const QVector<int>& columnWidth) const {
    int rowHeight = 20;

    // Рисуем текст для каждого столбца с использованием переданных ширин
    painter.drawText(x, y, columnWidth[0], rowHeight, Qt::AlignCenter, QString::fromStdString(title));
    painter.drawText(x + columnWidth[0], y, columnWidth[1], rowHeight, Qt::AlignCenter, QString::number(year));
    painter.drawText(x + columnWidth[0] + columnWidth[1], y, columnWidth[2], rowHeight, Qt::AlignCenter, QString::fromStdString(genre));
    painter.drawText(x + columnWidth[0] + columnWidth[1] + columnWidth[2], y, columnWidth[3], rowHeight, Qt::AlignCenter, QString::number(rating));
    painter.drawText(x + columnWidth[0] + columnWidth[1] + columnWidth[2] + columnWidth[3], y, columnWidth[4], rowHeight, Qt::AlignCenter, QString::fromStdString(director));
    painter.drawText(x + columnWidth[0] + columnWidth[1] + columnWidth[2] + columnWidth[3] + columnWidth[4], y, columnWidth[5], rowHeight, Qt::AlignCenter, is_available ? "Yes" : "No");
}

QSize films::textBlockSize(QPainter &painter) const {
    int rowHeight = 20;
    int width = painter.fontMetrics().horizontalAdvance(QString::fromStdString(title)) + 20; // Учитываем ширину заголовка
    return QSize(width, rowHeight);
}
