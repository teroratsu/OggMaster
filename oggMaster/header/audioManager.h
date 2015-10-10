#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "SoundStream.h"

class audioManager
{
    public:
        audioManager();
        audioManager(sf::String);
        virtual ~audioManager();

        bool loadMusic(sf::String = ""); //load music in buffer
        void play();
        void pause();
        void stop();
        void seek(sf::Time);

    private:
        void init();//init Soundstream object with buffer data

        SoundStream stream_;
        sf::SoundBuffer buffer_;
        sf::String filename_;
};

#endif // AUDIOMANAGER_H
