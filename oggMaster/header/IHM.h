#ifndef IHM_H
#define IHM_H

#include <iostream>
#include <string>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include "AudioManager.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class IHM
{
public:
    IHM();
    IHM(sf::String);
    // Our button click handler.
    void OnLoadBtnClick();
    void OnPlayBtnClick();
    void OnPauseBtnClick();
    void OnStopBtnClick();
    void PlayMusic(sf::String);

    void Run();

private:
    // Create an SFGUI object. This is required before doing anything with SFGUI.
    sfg::SFGUI m_sfgui;

    // Create the label pointer here to reach it from OnButtonClick().
    sfg::Label::Ptr m_label;

    AudioManager manager;
    sf::String fileName;
};

#endif // IHM_H
