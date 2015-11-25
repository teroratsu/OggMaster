#ifndef SOUNDWAVEDISPLAYER_H
#define SOUNDWAVEDISPLAYER_H

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/Window.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>

class SoundWaveDisplayer
{
    public:
    //! draw function, must be inherited by another class, SoundWaveDisplayer is an abstract class
    /*!
      \param f data array, the one to work with
      \param avg average power, based on the data
      \param of playing offset
      \param s _stream status
    */
        virtual void draw(float* f,float avg,sf::Time of,sf::SoundSource::Status s)=0;
};

#endif // SOUNDWAVEDISPLAYER_H
