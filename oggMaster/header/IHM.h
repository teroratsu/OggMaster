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
    IHM();//!< ctor
    ~IHM();//!< dtor
    //! starting point of the GUI
    void Run();

private:
    //! Init the whole GUI components
    /*!
        \sa IHM()
    */
    void initComponent();
    //! update GUI by getting data from the audio manager
    /*!
      \sa initComponent()
    */
    void update();
    //! specific update of the audio Visualization canvas
    /*!
        \sa update()
    */
    void updateCanvas();

    void OnLoadBtnClick();//!< refresh file list in the loader tab after loading new files
    void OnLoadMusicBtnClick(std::string);//!< call the playMusic function with fucntion param as argument

    void OnPlayBtnClick();//!< ask audio manager to play the actual buffer
    void OnPauseBtnClick();//!< ask audio manager to pause the actual buffer
    void OnStopBtnClick();//!< ask audio manager to stop the actual buffer
    void OnNextBtnClick();//!< ask audio manager to select and play the next song in the list
    void OnPrevBtnClick();//!< ask audio manager to select and play the previous song in list
    //!< simple division to be able to seek buffer to the good time according to the mouse click
    void OnSeek();//!< seek at the desired time according to the cursor position on event
    void OnVolumeChange();//!< change volume of the stream (by asking the manager) according to the cursor position on event

    //! ask the audioManager to play the desired file
    /*!
      \param s desired file
    */
    void PlayMusic(sf::String s);

    //void drawSoundWave(float*);

    AudioManager manager;
    std::vector<File> _files;
    unsigned int _filesPacked;

    sf::RenderWindow* render_window;
    sfg::SFGUI m_sfgui; // Create an SFGUI object. This is required before doing anything with SFGUI.

    //!< Desktop containing the main window
    sfg::Desktop _desktop;

    //!< Main window containing the whole pannels
    sfg::Window::Ptr _mainWindow;

    //!< TabPanel
    sfg::Notebook::Ptr _tabPanel;

    //!< Components of each page are stored in a box
    sfg::Box::Ptr _tabPlayerBox;//implemented
    sfg::Box::Ptr _tabLoaderBox;//implemented
    sfg::Box::Ptr _tabSettingsBox;//not yey
    sfg::Box::Ptr _tabRecorderBox;//not yet
    sfg::Box::Ptr _tabConverterBox;//not yet


    //! < TAB PLAYER >
        //!< Create the Buttons (smart pointers)
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

    //! < TAB LOADER >
        //!< Create the Entry
        sfg::Button::Ptr _loadBtn;
        sfg::Entry::Ptr _entryLoader;
        sfg::CheckButton::Ptr _iterateSubFolders;
        sfg::Box::Ptr _listFiles;
        void packFile(File);

        sfg::Box::Ptr _boxEntry;
        sfg::ScrolledWindow::Ptr _listfilesHolder;
        sfg::Frame::Ptr _BoxFrameEntry;

    //!< init data :
    sf::Sprite _logoOgg;
    sf::Texture _logoOgg_tex;
    sf::Sprite _nameHolder;
    sf::Texture _nameHolder_tex;

    sf::Font _font;
    sf::Text _curSong;
    sf::Text _curDuration;

    sf::Image _playImg;
    sf::Image _pauseImg;
    sf::Image _stopImg;
    sf::Image _nextImg;
    sf::Image _prevImg;

    //!< update data :
    sf::Clock clock_Manager;
    sf::Clock clock_Displayer;
};

#endif // IHM_H
