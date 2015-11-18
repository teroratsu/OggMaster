#ifndef SOUNDSTREAM_H
#define SOUNDSTREAM_H

#include <SFML/Audio.hpp> //sf::SoundStream
#include <vector>
#include <iostream>
#include <memory>
#include "Observer.h"

class SoundStream : public sf::SoundStream
{
    public:
        SoundStream();
        SoundStream(Observer*);//default ctor
        virtual ~SoundStream();
        void load(const sf::SoundBuffer&); //! load
        void seek(sf::Time); //!< seek to the desired time according to the audio file duration

        sf::Time getPOffset();

        void updateObs(); //!< notify Observer with time elasped
        bool isBufferEnd();

        void Attach(Observer*);
        void Detach(Observer*);

    private:

        /**
           * notify observers with the chunk actually played and additional data
           * @param sf::SoundStream::Chunk& : Chunk of data to be sent.
           * @param unsigned int : Sample rate. sample/s
           * @param unsigned int : Channel count.
           * @param unsigned std::size_t : 'pointer' to the first sample.
           * @see Notify(sf::Time), SoundStream(Observer*),
        */
        void Notify(sf::SoundStream::Chunk&, unsigned int, unsigned int, std::size_t);
                /**
           * notify observers with the currently played sample
           * @param sf::Time : position of the current sample relative to the beginning of the audio flux.
           * @see SoundStream(Observer*), sf::SoundStream::Chunk&::m_samples
        */
        void Notify(sf::Time);

        std::vector<Observer*> _listObserver;

        std::vector<sf::Int16> m_samples; //! samples from the buffer
        std::size_t m_currentSample; //! current sample (the "to be played" one)
        bool bufferEnd;

        virtual bool onGetData(Chunk&);
        virtual void onSeek(sf::Time);
};

#endif // SOUNDSTREAM_H
