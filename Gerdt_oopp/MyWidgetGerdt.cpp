#include "MyWidgetGerdt.h"
#include <QPainter>
#include <QMouseEvent>
#include "pch.h"

MyWidgetGerdt::MyWidgetGerdt(QWidget *parent) : QWidget{parent} {}

void MyWidgetGerdt::load(const QString& path) {
    filmList.clear();
    ifstream in(path.toStdWString(), ifstream::binary);
    if (in) {
        try {
            boost::archive::binary_iarchive ar(in);
            ar >> filmList;
            qDebug() << "Data loaded successfully, filmList size:" << filmList.size();
            update();
        } catch (const exception &e) {
            qDebug() << "Error during deserialization:" << e.what();
        }
    } else {
        qDebug() << "Failed to open file for loading.";
    }
}

void MyWidgetGerdt::clean() {
    filmList.clear();
    update();
}

void MyWidgetGerdt::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QFont font("DejaVu Sans", 10);
    painter.setFont(font);
    int x = 10, y = 10;
    int rowHeight = 30;

    QStringList headers = {
        QString::fromUtf8("Название"),
        QString::fromUtf8("Год"),
        QString::fromUtf8("Жанр"),
        QString::fromUtf8("Рейтинг"),
        QString::fromUtf8("Режиссёр"),
        QString::fromUtf8("В прокате?"),
        QString::fromUtf8("Актеры озвучки"),
        QString::fromUtf8("Стиль анимации")
    };
    int columnCount = headers.size();

    QVector<QStringList> tableData;
    tableData.append(headers);

    if (!filmList.empty()) {
    // Заполняем таблицу данными из filmList с использованием for_each и bind
    for_each(filmList.begin(), filmList.end(), bind([&](const auto& film) {
                      QStringList values;
                      if (auto animatedFilm = dynamic_cast<AnimatedFilm*>(film.get())) {
                          values << QString::fromLocal8Bit(animatedFilm->getTitle())
                          << QString::number(animatedFilm->getYear())
                          << QString::fromLocal8Bit(animatedFilm->getGenre())
                          << QString::number(animatedFilm->getRating())
                          << QString::fromLocal8Bit(animatedFilm->getDirector())
                          << (animatedFilm->isAvailable() ? QString::fromUtf8("Да") : QString::fromUtf8("Нет"))
                          << QString::fromLocal8Bit(animatedFilm->getVoiceActors())
                          << QString::fromLocal8Bit(animatedFilm->getAnimationStyle());
                      } else {
                          values << QString::fromLocal8Bit(film->getTitle())
                          << QString::number(film->getYear())
                          << QString::fromLocal8Bit(film->getGenre())
                          << QString::number(film->getRating())
                          << QString::fromLocal8Bit(film->getDirector())
                          << (film->isAvailable() ? QString::fromUtf8("Да") : QString::fromUtf8("Нет"))
                          << "-" << "-";
                      }
                      tableData.append(values);
                  }, placeholders::_1));

    QVector<int> columnWidths(columnCount, 100);
    for (int i = 0; i < columnCount; ++i) {
       for_each(tableData.begin(), tableData.end(), bind([&](const QStringList& row) {
                          columnWidths[i] = max(columnWidths[i], painter.fontMetrics().horizontalAdvance(row[i]) + 20);
                      }, placeholders::_1));
    }

    int totalWidth = accumulate(columnWidths.begin(), columnWidths.end(), 0) + 20;
    int totalHeight = tableData.size() * rowHeight + 20;

    setMinimumSize(totalWidth, totalHeight);
    setGeometry(geometry().x(), geometry().y(), totalWidth, totalHeight);

    for_each(tableData.begin(), tableData.end(), bind([&](const QStringList& row) {
                      x = 10;
                      for (int i = 0; i < row.size(); ++i) {
                          QString text = row[i];
                          painter.drawText(x, y, columnWidths[i], rowHeight, Qt::AlignCenter, text);
                          x += columnWidths[i];
                      }
                      y += rowHeight;
                  }, placeholders::_1));


    int tableWidth = accumulate(columnWidths.begin(), columnWidths.end(), 0);
    int rowIndex = 0;
    for_each(tableData.begin(), tableData.end(), bind([&](const QStringList&) {
                      painter.drawLine(10, 10 + rowIndex * rowHeight, 10 + tableWidth, 10 + rowIndex * rowHeight);
                      ++rowIndex;
                  }, placeholders::_1));
    painter.drawLine(10, 10 + tableData.size() * rowHeight, 10 + tableWidth, 10 + tableData.size() * rowHeight);

    // Рисуем вертикальные линии сетки с использованием for_each и bind
    x = 10;
    for_each(columnWidths.begin(), columnWidths.end(), bind([&](int width) {
                      painter.drawLine(x, 10, x, y);
                      x += width;
                  }, placeholders::_1));
    painter.drawLine(x, 10, x, y);
}
}
