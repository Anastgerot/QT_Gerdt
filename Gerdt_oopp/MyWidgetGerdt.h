#pragma once

#include <QWidget>
#include "pch.h"
#include "films.h"
#include "AnimatedFilm.h"


class MyWidgetGerdt : public QWidget {
public:
    vector<shared_ptr<films>> filmList;
    vector<shared_ptr<films>> getfilmList() const { return filmList; }
    explicit MyWidgetGerdt(QWidget *parent = nullptr);
    void load(const QString& path);
    void clean();

protected:
    void paintEvent(QPaintEvent *event) override;
};

