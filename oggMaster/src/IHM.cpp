#include "../header/IHM.h"

IHM::IHM()
{
    this->fileName = "./bin/Debug/music.ogg";
}

IHM::IHM(sf::String fileName):manager(fileName)
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
}

void IHM::OnPauseBtnClick()
{
    manager.pause();
}

void IHM::Run()
{
    //fada_Manager* fada = fada_newmanager();
    //fada_freechunks(fada_newmanager());

    // Create SFML's window.
    sf::RenderWindow render_window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "Wanna play some music ?" );

    // Create the label.
    m_label = sfg::Label::Create( "Here i come" );

    // Create a simple button and connect the click signal.
    auto button = sfg::Button::Create( "Load music" );
    button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnLoadBtnClick, this ) );
    auto button1 = sfg::Button::Create( "PLAY" );
    button1->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnPlayBtnClick, this ) );
    auto button2 = sfg::Button::Create( "STOP" );
    button2->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnPauseBtnClick, this ) );

    // Create a vertical box layouter with 5 pixels spacing and add the label
    // and button to it.
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 50.0f);
    box->Pack( m_label );
    box->Pack( button, false );
    box->Pack( button1, false );
    box->Pack( button2, false );

    // Create a window and add the box layouter to it. Also set the window's title.
    auto window = sfg::Window::Create();
    window->SetTitle( "OGG master" );
    window->Add( box );

    // Create a desktop and add the window to it.
    sfg::Desktop desktop;
    desktop.Add( window );

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
            desktop.HandleEvent( event );

            // If window is about to be closed, leave program.
            if( event.type == sf::Event::Closed )
            {
                render_window.close();
            }
        }

        // Update SFGUI with elapsed seconds since last call.
        desktop.Update( clock.restart().asSeconds() );

        // Rendering.
        render_window.clear();
        m_sfgui.Display( render_window );
        render_window.display();
    }
}
