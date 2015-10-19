#ifndef SOUNDSTREAM_H
#define SOUNDSTREAM_H

#include <SFML/Audio.hpp> //sf::SoundStream
#include <vector>
#include <memory>
#include "Observer.h"

class SoundStream : public sf::SoundStream
{
    public:
        SoundStream();
        SoundStream(Observer*);//default ctor
        virtual ~SoundStream();
        void load(const sf::SoundBuffer&); //! load
        void seek(sf::Time); //! seek to the desired time according to the audio file duration

        void Attach(Observer*);
        void Detach(Observer*);
        void Notify(sf::SoundStream::Chunk&);

        std::vector<Observer*> _listObserver;

    private:
        std::vector<sf::Int16> m_samples; //! samples from the buffer
        std::size_t m_currentSample; //! current sample (the "to be played" one)

        virtual bool onGetData(Chunk&);
        virtual void onSeek(sf::Time);
};

#endif // SOUNDSTREAM_H
