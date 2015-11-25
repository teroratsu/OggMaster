#ifndef OBSERVER_H
#define OBSERVER_H

#include "SFML/Audio.hpp"

class Observer
{
public:
    //! update with a new chunk of data
    /*!
      \param c chunk of data
      \param s_r Sample rate
      \param c_c Channel count
      \param s first sample of the chunk
      \sa update()
    */
    virtual void update(sf::SoundStream::Chunk& c , unsigned int s_r, unsigned int c_c, std::size_t s) = 0; //chunk of sample & sample rate (samples/s) & Channel count & base Sample
    //! update Soundwave with a given time offset
    /*!
      \param t time offset
      \sa update()
    */
    virtual void update(sf::Time t) = 0;//force data refresh
};

#endif // OBSERVER_H
