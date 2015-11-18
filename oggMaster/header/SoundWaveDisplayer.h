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
        virtual void draw(float*,float,sf::Time,sf::SoundSource::Status)=0;
};

#endif // SOUNDWAVEDISPLAYER_H
