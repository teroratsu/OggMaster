#ifndef SOUNDSTREAM_H
#define SOUNDSTREAM_H

#include <SFML/Audio.hpp>

class SoundStream : public sf::SoundStream
{
    public:
        SoundStream();
        virtual ~SoundStream();
        void load(const sf::SoundBuffer&);
        void seek(sf::Time);

    private:
        std::vector<sf::Int16> m_samples;
        std::size_t m_currentSample;

        virtual bool onGetData(Chunk&);
        virtual void onSeek(sf::Time);
};

#endif // SOUNDSTREAM_H
