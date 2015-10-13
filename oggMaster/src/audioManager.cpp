#include "../header/audioManager.h"

audioManager::audioManager()
{
    //ctor
    _stream = std::make_shared<SoundStream>();
    _buffer = std::make_shared<sf::SoundBuffer>();
    _wave   = std::make_shared<SoundWave>();

    this->_filename = "./bin/Debug/music.ogg"; //default file loaded
}

audioManager::audioManager(sf::String filename)
{
    if(filename == "")
        this->_filename = "./bin/Debug/music.ogg"; //default file loaded
    else
        this->_filename = filename;

    _stream = std::make_shared<SoundStream>();
    _buffer = std::make_shared<sf::SoundBuffer>();
    _wave   = std::make_shared<SoundWave>();
}

audioManager::~audioManager()
{
    _stream->stop();
}

bool audioManager::loadMusic(sf::String filename)
{
    bool initBuffer;
    if(!_filename.isEmpty())
        initBuffer = _buffer->loadFromFile(filename);
    else
        initBuffer = _buffer->loadFromFile(_filename);
    init();

    return initBuffer;
}

void audioManager::init()
{
    _stream->load(*_buffer);
}

void audioManager::play()
{
    if(_stream->getStatus() != SoundStream::Playing)
        _stream->play();
}

void audioManager::pause()
{
    if(_stream->getStatus() != SoundStream::Paused)
        _stream->pause();
}

void audioManager::stop()
{
    if(_stream->getStatus() != SoundStream::Stopped)
        _stream->stop();
}

void audioManager::seek(sf::Time timeOffset)
{
    _stream->seek(timeOffset);
}
