#ifndef SOUNDSTREAM_H
#define SOUNDSTREAM_H

#include <SFML/Audio.hpp>
#include "StreamSubject.h"

class SoundStream : public sf::SoundStream, public StreamSubject
{
    public:
        SoundStream();
        virtual ~SoundStream();
        void load(const sf::SoundBuffer&); //! load
        void seek(sf::Time); //! seek to the desired time according to the audio file

        sf::SoundStream::Chunk getLastChunk();//!< return the latest chunk to be played

    private:
        std::vector<sf::Int16> m_samples; //! samples from the buffer
        std::size_t m_currentSample; //! current sample (the to be played one)
        sf::SoundStream::Chunk _chunk;

        virtual bool onGetData(Chunk&);
        virtual void onSeek(sf::Time);
};

#endif // SOUNDSTREAM_H
