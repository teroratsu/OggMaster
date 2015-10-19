#include "../header/IHM.h"

IHM::IHM()
{
    this->fileName = "./bin/Debug/music.ogg";
}

IHM::IHM(sf::String fileName): manager(fileName)
{
    if(fileName == "")
        this->fileName = "./bin/Debug/music.ogg";
    else
        this->fileName = fileName;
}

void IHM::OnLoadBtnClick()
{
    if(!manager.loadMusic(fileName))
        m_label->SetText( "Music don't load :( (ogg file ?)\n" ); // error
    m_label->SetText( "FILENAME GETTER NOT HANDLE YET !" );
}

void IHM::PlayMusic(sf::String filename)
{
    this->fileName = filename;
    if (!manager.loadMusic(fileName));
    m_label->SetText( fileName + " won't load. \n" ); // error
    manager.play();
    m_label->SetText("playing !");
}

void IHM::OnPlayBtnClick()
{
    manager.play();
    manager.test();
}

void IHM::OnPauseBtnClick()
{
    manager.pause();
}

void IHM::OnStopBtnClick()
{
    manager.stop();
}

void IHM::Run()
{

    // Create SFML's window.
    sf::RenderWindow render_window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "Wanna play some music ?" );

    // Create the label.
    m_label = sfg::Label::Create( "Please, load a music file!");

    // Create a simple button and connect the click signal.
    _loadBtn = sfg::Button::Create( "LOAD" );
    _loadBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnLoadBtnClick, this ) );
    _playBtn = sfg::Button::Create( "PLAY" );
    _playBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnPlayBtnClick, this ) );
    _pauseBtn = sfg::Button::Create( "PAUSE" );
    _pauseBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnPauseBtnClick, this ) );
    _stopBtn = sfg::Button::Create( "STOP" );
    _stopBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnStopBtnClick, this ) );

    // Create a vertical box layouter with 5 pixels spacing and add the label
    // and button to it.
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL,5.f);
    box->Pack( m_label );
    box->Pack( _loadBtn, false );
    box->Pack( _playBtn, false );
    box->Pack( _pauseBtn, false );
    box->Pack( _stopBtn, false );

    // Create a window and add the box layouter to it. Also set the window's title.
    _window = sfg::Window::Create();
    _window->SetTitle( "OGG master" );
    _window->Add( box );

    // Create a desktop and add the window to it.
    /*sfg::Desktop desktop;
    desktop.Add( window );*/

    // We're not using SFML to render anything in this program, so reset OpenGL
    // states. Otherwise we wouldn't see anything.
    render_window.resetGLStates();

    // Main loop!
    sf::Event event;
    sf::Clock clock;

    if(fileName != "./bin/Debug/music.ogg")//si le fichier contenu est différent de celui par défaut
    {
        PlayMusic(fileName);//on auto-play le morceau au lancement
    }

    while( render_window.isOpen() )
    {
        // Event processing.
        while( render_window.pollEvent( event ) )
        {
            //desktop.HandleEvent( event );
            _window->HandleEvent( event );

            // If window is about to be closed, leave program.
            if( event.type == sf::Event::Closed )
            {
                render_window.close();
            }
        }

        // Update SFGUI with elapsed seconds since last call.
        //desktop.Update( clock.restart().asSeconds() );

        // Rendering.
        _window->Update( 0.f );
        render_window.clear();
        m_sfgui.Display( render_window );
        render_window.display();
    }
}
