#pragma once

#include <QWidget>
#include "pch.h"
#include "films.h"
#include "AnimatedFilm.h"


class MyWidgetGerdt : public QWidget {
public:
    std::vector<std::shared_ptr<films>> filmList;
    std::vector<std::shared_ptr<films>> getfilmList() const { return filmList; }
    explicit MyWidgetGerdt(QWidget *parent = nullptr);
    void load(const QString& path);
    void clean();

protected:
    void paintEvent(QPaintEvent *event) override;
};

BOOST_SERIALIZATION_SPLIT_FREE(QPointF)

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive & ar, const QPointF& p, const unsigned int) {
    ar << p.x();
    ar << p.y();
}

template<class Archive>
void load(Archive & ar, QPointF& p, const unsigned int) {
    qreal x, y;
    ar >> x;
    ar >> y;
    p.setX(x);
    p.setY(y);
}

}
}
