#ifndef OBSERVER_H
#define OBSERVER_H

#include "SFML/Audio.hpp"

class Observer
{
    public:
        virtual void update(sf::SoundStream::Chunk&, unsigned int, unsigned int, std::size_t) = 0; //chunk of sample & sample rate (samples/s) & Channel count & base Sample
        virtual void update(sf::Time) = 0;//force data refresh
};

#endif // OBSERVER_H
