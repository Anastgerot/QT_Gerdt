#pragma once

#include <QString>
#include <QPainter>
#include "pch.h"

class films {
    friend class boost::serialization::access;

protected:
    std::string title;
    int year;
    std::string genre;
    double rating;
    std::string country;
    std::string director;
    bool is_available;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & title;
        ar & year;
        ar & genre;
        ar & rating;
        ar & country;
        ar & director;
        ar & is_available;
    }

public:
    virtual ~films() = default;

    std::string getTitle() const { return title; }
    int getYear() const { return year; }
    std::string getGenre() const { return genre; }
    double getRating() const { return rating; }
    std::string getDirector() const { return director; }
    bool isAvailable() const { return is_available; }

    virtual void draw(QPainter &painter, int x, int y, const QVector<int>& columnWidth) const;

    virtual QSize textBlockSize(QPainter &painter) const;
};
