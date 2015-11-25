#include "../header/IHM.h"

IHM::IHM() //: _LinesL_b(sf::PrimitiveType::Lines, 256), _LinesR_b(sf::PrimitiveType::Lines, 256),_LinesL_h(sf::PrimitiveType::Lines, 256),_LinesR_h(sf::PrimitiveType::Lines, 256)
{
    initComponent();
    manager.loadMusicFromFolder("./playMe");
    manager.getAllFiles(_files);

    _listfilesHolder->Remove( _listFiles );
    _listFiles = sfg::Box::Create( sfg::Box::Orientation::VERTICAL,5.f );
    for(std::vector<File>::iterator it = _files.begin() ; it != _files.end(); ++it)
        packFile(*it);
    _listfilesHolder->AddWithViewport( _listFiles );
}

IHM::~IHM()
{
    delete _soundwave;
    delete render_window;
}

void IHM::PlayMusic(sf::String filename)
{
    /*this->fileName = filename;
    if (!manager.loadMusic(fileName));
    m_label->SetText( fileName + " won't load. \n" ); // error
    manager.play();
    m_label->SetText("playing !");*/
}

void IHM::OnPlayBtnClick()
{
    manager.play();
}

void IHM::OnPauseBtnClick()
{
    manager.pause();
}

void IHM::OnStopBtnClick()
{
    manager.stop();
}

void IHM::OnNextBtnClick()
{
    manager.next();
}

void IHM::OnPrevBtnClick()
{
    manager.prev();
}

void IHM::OnLoadBtnClick()
{
    manager.loadMusicFromFolder(_entryLoader->GetText(), _iterateSubFolders->IsActive());//load
    manager.getAllFiles(_files);

    _listfilesHolder->Remove( _listFiles );
    _listFiles = sfg::Box::Create( sfg::Box::Orientation::VERTICAL,5.f);
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 300.f);
    _listFiles->Pack( box, false);
    for(std::vector<File>::iterator it = _files.begin() ; it != _files.end(); ++it)
        packFile(*it);
    _listfilesHolder->AddWithViewport( _listFiles );
}

void IHM::OnLoadMusicBtnClick(std::string f_)
{
    manager.loadMusic(f_); //filename
    manager.play();
}

void IHM::OnSeek()
{
    sf::FloatRect r_ = _songDuration->GetAllocation();
    sf::Vector2i m_p = sf::Mouse::getPosition(*render_window);
    float p_ = (m_p.x - 17) / (r_.width);// -17px à cause de l'auto layout
    manager.seek(p_);
    _songDuration->SetFraction(manager.getDurationP());
}

void IHM::OnVolumeChange()
{
    sf::FloatRect r_ = _volume->GetAllocation();
    sf::Vector2i m_p = sf::Mouse::getPosition(*render_window);
    float p_ = (r_.height- (m_p.y-41))/r_.height;//    manager.setVolume(p_);
    _volume->SetFraction(manager.getVolume());
}

void IHM::Run()
{
    // Main loop!
    sf::Event event;
    sf::Clock clock;

    while( render_window->isOpen() )
    {
        // Event processing.
        while( render_window->pollEvent( event ) )
        {
            //_desktop.HandleEvent( event );
            _desktop.HandleEvent( event );

            // If window is about to be closed, leave program.
            if( event.type == sf::Event::Closed )
            {
                render_window->close();
            }

            switch(event.type)
            {
            case sf::Event::KeyPressed :
                {
                    if(event.key.code == sf::Keyboard::Right)
                        OnNextBtnClick();
                    else
                    {
                        if(event.key.code == sf::Keyboard::Left)
                            OnPrevBtnClick();
                    }
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        if(manager.getStatus() == SoundStream::Playing)
                            OnPauseBtnClick();
                        else
                            OnPlayBtnClick();
                    }
                }break;
            }
        }
        if( clock.getElapsedTime().asMicroseconds() >= 5000 ) {
			// Update() takes the elapsed time in seconds.
			_desktop.Update( static_cast<float>( clock.getElapsedTime().asMicroseconds() ) / 1000000.f );

			clock.restart();
		}

        update();//global update

        render_window->clear();

        m_sfgui.Display(*render_window );

        //m_label->SetText( manager.getDuration() );

        render_window->display();
    }
}

void IHM::updateCanvas()
{
    _canvas->Bind();
    _canvas->Clear( sf::Color( 0, 0, 0, 0 ) );
    _canvas->Draw( _logoOgg );
    _soundwave->draw(manager.getSoundwave(),manager.getAvgPower(), clock_Displayer.restart(),manager.getStatus());
    _canvas->Draw( _nameHolder );
    _canvas->Draw(_curSong);
    _canvas->Draw(_curDuration);
    _canvas->Display();
    _canvas->Unbind();
}

void IHM::update(){
            // Update the GUI every 5ms
    if(manager.getStatus() == SoundStream::Playing)
    {
        _songDuration->SetFraction(manager.getDurationP());
    }
    if(manager.getStatus() == SoundStream::Stopped)
        _songDuration->SetFraction(0.0f);
    if(clock_Manager.getElapsedTime().asMicroseconds() >= 25000){
        manager.update();
        _curSong.setString(manager.getCurPlayingSong());
        _curDuration.setString(manager.getDuration());
        sf::FloatRect _localBounds;
        _localBounds = _curSong.getLocalBounds();
        _curSong.setOrigin(_localBounds.width/2,_localBounds.height/2);
        _localBounds = _curDuration.getLocalBounds();
        _curDuration.setOrigin(_localBounds.width/2,_localBounds.height/2);
        _curSong.setPosition(400,270);
        _curDuration.setPosition(400,320);
        clock_Manager.restart();
    }
    updateCanvas();
}

void IHM::packFile(File f_)
{
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 50.f);
    box->Pack( sfg::Label::Create( f_.getFilename() ), true, true );
    box->Pack( sfg::Label::Create( f_.getFilepath() ), true, true );
    auto button = sfg::Button::Create( L"Load" );
    //auto funct = std::bind( &IHM::OnLoadMusicBtnClick, f_.getFilename());
    auto funct = std::bind(&IHM::OnLoadMusicBtnClick,this, f_.getFilename());//need to try this
    button->GetSignal( sfg::Widget::OnLeftClick ).Connect( funct );
    box->Pack( button, false );
    _listFiles->Pack( box, false);
}

    void IHM::initComponent()
    {
        render_window = new sf::RenderWindow( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "OGG MASTER" , sf::Style::Titlebar | sf::Style::Close);
        render_window->resetGLStates();//not sfml that draw

        _mainWindow = sfg::Window::Create( sfg::Window::Style::BACKGROUND);

        _filesPacked = 5;

        //!< Player >
            /*_loadBtn = sfg::Button::Create( "LOAD" );
            _loadBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnLoadBtnClick, this ) );*/
            _playBtn = sfg::Button::Create("PLAY");
            _playBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnPlayBtnClick, this ) );
            _pauseBtn = sfg::Button::Create( "PAUSE" );
            _pauseBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnPauseBtnClick, this ) );
            _stopBtn = sfg::Button::Create( "STOP" );
            _stopBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnStopBtnClick, this ) );
            _nextBtn = sfg::Button::Create( "->" );
            _nextBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnNextBtnClick, this ) );
            _prevBtn = sfg::Button::Create( "<-" );
            _prevBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnPrevBtnClick, this ) );

            //Create the canvas
            _canvas = sfg::Canvas::Create();

            //_logoOgg_tex.loadFromFile("./bin/Debug/oggPro.png");
            _logoOgg_tex.loadFromFile("./Assets/BG.jpg");
            _nameHolder_tex.loadFromFile("./Assets/SoundNameHandler.png");

            _logoOgg.setTexture(_logoOgg_tex);
            _nameHolder.setTexture(_nameHolder_tex);

            sf::FloatRect _localBounds = _logoOgg.getLocalBounds();
            _logoOgg.setOrigin(_localBounds.width/2,_localBounds.height/2);
            _logoOgg.setPosition(400,300);

            _font.loadFromFile("./Assets/font.ttf");
            _curSong.setFont(_font);
            _curSong.setString("Click the play button ! (default song)");
            _curSong.setCharacterSize(20);
            _curDuration.setFont(_font);
            _curDuration.setCharacterSize(15);
            _localBounds = _curSong.getLocalBounds();
            _curSong.setOrigin(_localBounds.width/2,_localBounds.height/2);

            _curSong.setPosition(400,300);

            _canvas->SetRequisition( sf::Vector2f( sf::Vector2f(800.0f,600.0f ) ) );
            _soundwave = new LineDisplayer(_canvas,15,1024);

            _volume = sfg::ProgressBar::Create(sfg::ProgressBar::Orientation::VERTICAL);
            _volume->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnVolumeChange, this ) );
            _volume->SetFraction(manager.getVolume());

            _songDuration = sfg::ProgressBar::Create(sfg::ProgressBar::Orientation::HORIZONTAL);
            _songDuration->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnSeek, this ) );

            _boxAffPlayer = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL,10.f);
            _boxAffPlayer->Pack( _canvas, true, true);
            _boxAffPlayer->Pack( _volume, true, true);

            _boxToolbar = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL,10.f);
            _boxToolbar->Pack( _prevBtn, true, true);
            _boxToolbar->Pack( _playBtn, true, true );
            _boxToolbar->Pack( _pauseBtn, true, true );
            _boxToolbar->Pack( _stopBtn, true, true );
            //_boxToolbar->Pack( _loadBtn, true, true );
            _boxToolbar->Pack( _nextBtn, true, true);

            _BoxFrameToolbar = sfg::Frame::Create(L"Toolbar");
            _BoxFrameToolbar->Add(_boxToolbar);

            _tabPlayerBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
            _tabPlayerBox->SetSpacing(5.f);
            _tabPlayerBox->Pack(_boxAffPlayer);
            _tabPlayerBox->Pack(_boxToolbar);
            _tabPlayerBox->Pack(_songDuration);
        //!< End Player >

        //!< Loader >
            _loadBtn = sfg::Button::Create("Load Folder");
            _loadBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &IHM::OnLoadBtnClick, this ) );
            _entryLoader = sfg::Entry::Create("./musique");
            _iterateSubFolders = sfg::CheckButton::Create( "iterate sub folders" );

            _boxEntry = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL,20.f);
            _boxEntry->Pack( _loadBtn, true, true);
            _boxEntry->Pack( _entryLoader, true, true);
            _boxEntry->Pack( _iterateSubFolders, true, true);

            _BoxFrameEntry = sfg::Frame::Create(L"Load files from folder");
            _BoxFrameEntry->Add(_boxEntry);

            _listFiles = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
            auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 300.f);
            box->Pack( sfg::Label::Create( L"FileName"), true );
            box->Pack( sfg::Label::Create( L"Path" ), true, true );
            box->Pack( sfg::Label::Create( L"Load" ), true );
            _listFiles->Pack( box, false);

            _listfilesHolder = sfg::ScrolledWindow::Create();
            _listfilesHolder->SetRequisition( sf::Vector2f( .0f, 550.f ) );
            _listfilesHolder->SetScrollbarPolicy( sfg::ScrolledWindow::HORIZONTAL_AUTOMATIC | sfg::ScrolledWindow::VERTICAL_AUTOMATIC );
            _listfilesHolder->SetPlacement( sfg::ScrolledWindow::Placement::TOP_LEFT );
            _listfilesHolder->AddWithViewport( _listFiles );

            _tabLoaderBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
            _tabLoaderBox->SetSpacing(5.f);
            _tabLoaderBox->Pack(_BoxFrameEntry);
            _tabLoaderBox->Pack(_listfilesHolder);
        //!< End Loader >

        //!< building TabPanel >
            _tabPanel = sfg::Notebook::Create();
            _tabPanel->SetTabPosition( sfg::Notebook::TabPosition::TOP );
            _tabPanel->AppendPage( _tabPlayerBox, sfg::Label::Create( "Player" ) );
            _tabPanel->AppendPage( _tabLoaderBox, sfg::Label::Create( "Loader" ) );

        _mainWindow->Add(_tabPanel);
        //_mainWindow->SetPosition(sf::Vector2f( 0.f, -20.f ));

        // Create a desktop and add the window to it.
        _desktop.Add( _tabPanel);
        _desktop.Update( 0.f );
    }
