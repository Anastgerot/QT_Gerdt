#pragma once

#include "pch.h"
#include "films.h"

class AnimatedFilm : public films {
    friend class boost::serialization::access;

protected:
    string voice_actors = "";
    string animation_style = "";

public:
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    virtual ~AnimatedFilm() = default;

    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
        ar & boost::serialization::base_object<films>(*this);
        ar & voice_actors;
        ar & animation_style;
    }

    template<class Archive>
    void load(Archive& ar, const unsigned int version) {
        ar & boost::serialization::base_object<films>(*this);
        ar & voice_actors;
        ar & animation_style;
    }

    string getVoiceActors() const { return voice_actors; }
    string getAnimationStyle() const { return animation_style; }
};
