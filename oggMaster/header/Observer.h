#ifndef OBSERVER_H
#define OBSERVER_H

#include "SFML/Audio.hpp"

class Observer
{
    public:
        virtual void update(sf::SoundStream::Chunk&) = 0;
};

#endif // OBSERVER_H
