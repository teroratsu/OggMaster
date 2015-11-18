#ifndef IHM_H
#define IHM_H

#include <iostream>
#include <string>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/Window.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "AudioManager.h"
#include "File.h"
#include "LineDisplayer.h"

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 705;

class IHM
{
public:
    IHM();
    ~IHM();
    // Our button click handler.
    void OnLoadBtnClick();
    void OnPlayBtnClick();
    void OnPauseBtnClick();
    void OnStopBtnClick();
    void OnNextBtnClick();
    void OnPrevBtnClick();
    //!< simple division to be able to seek buffer to the good time according to the mouse click
    void OnSeek();
    void OnVolumeChange();

    void PlayMusic(sf::String);

    void Run();

private:
    void initComponent();
    void update();
    void updateCanvas();

    //void drawSoundWave(float*);

    AudioManager manager;
    sf::String fileName;

    sf::RenderWindow* render_window;
    sfg::SFGUI m_sfgui; // Create an SFGUI object. This is required before doing anything with SFGUI.

    //!< Desktop containing the main window
    sfg::Desktop _desktop;

    //!< Main window containing the whole pannels
    sfg::Window::Ptr _mainWindow;

    //!< TabPanel
    sfg::Notebook::Ptr _tabPanel;

    //! < TAB PLAYER >
        //!< Components of each page are stored in a box
        sfg::Box::Ptr _tabPlayerBox;
        sfg::Box::Ptr _tabLoaderBox;
        sfg::Box::Ptr _tabSettingsBox;
        sfg::Box::Ptr _tabRecorderBox;
        sfg::Box::Ptr _tabConverterBox;

        //!< Create the Buttons (smart pointers)
        sfg::Button::Ptr _loadBtn;
        sfg::Button::Ptr _playBtn;
        sfg::Button::Ptr _pauseBtn;
        sfg::Button::Ptr _stopBtn;
        sfg::Button::Ptr _nextBtn;
        sfg::Button::Ptr _prevBtn;

        sfg::Box::Ptr _boxToolbar;
        sfg::Frame::Ptr _BoxFrameToolbar; //for the box

        //!< Create the canvas
        sfg::Canvas::Ptr _canvas;
        SoundWaveDisplayer* _soundwave;
        sfg::ProgressBar::Ptr _volume;

        sfg::Box::Ptr _boxAffPlayer;

        //!< Create the progress bar
        sfg::ProgressBar::Ptr _songDuration;

        sfg::Label::Ptr m_label; //actually useless

    //! < TAB LOADER >

        //empty

    //!< init data :
    sf::Sprite _logoOgg;
    sf::Texture _logoOgg_tex;
    sf::Sprite _nameHolder;
    sf::Texture _nameHolder_tex;

    sf::Font _font;
    sf::Text _curSong;
    sf::Text _curDuration;

    //!< update data :
    sf::Clock clock_Manager;
    sf::Clock clock_Displayer;
};

#endif // IHM_H
