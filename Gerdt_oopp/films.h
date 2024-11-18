#pragma once

#include <QString>
#include <QPainter>
#include "pch.h"

class films {
    friend class boost::serialization::access;
protected:
    string title;
    int year;
    string genre;
    double rating;
    string country;
    string director;
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

    string getTitle() const { return title; }
    int getYear() const { return year; }
    string getGenre() const { return genre; }
    double getRating() const { return rating; }
    string getCountry() const { return country; }
    string getDirector() const { return director; }
    bool isAvailable() const { return is_available; }

    void setTitle(const string& title) {this->title = title;}

    void setYear(int year) {this->year = year;}

    void setGenre(const string& genre) {this->genre = genre;}

    void setRating(int rating) {this->rating = rating;}

    void setCountry(const string& country) {this->country = country;}

    void setDirector(const string& director) {this->director = director;}

    void setAvailable(bool available) { this->is_available = available; }



};
