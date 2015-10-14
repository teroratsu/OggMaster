#include "../header/AudioManager.h"

AudioManager::AudioManager()
{
    //ctor
    _stream = std::make_shared<SoundStream>(); //!< init the _stream object with a instance of a SoundStream class
    _buffer = std::make_shared<sf::SoundBuffer>(); //!< init the _buffer object with a instance of a sf::SoundBuffer class
    _wave   = std::make_shared<SoundWave>(); //!< init the _wave object with a instance of a SoundWave class

    this->_filename = "./bin/Debug/music.ogg"; //default file loaded
}

AudioManager::AudioManager(sf::String filename)
{
    if(filename == "")
        this->_filename = "./bin/Debug/music.ogg"; //default file loaded
    else
        this->_filename = filename;

    _stream = std::make_shared<SoundStream>(); //!< init the _stream object with a instance of a SoundStream class
    _buffer = std::make_shared<sf::SoundBuffer>(); //!< init the _buffer object with a instance of a sf::SoundBuffer class
    _wave   = std::make_shared<SoundWave>(); //!< init the _wave object with a instance of a SoundWave class
}

AudioManager::~AudioManager()
{
    _stream->stop(); //!< The audio buffer must be stopped before destroying the actual AudioManager object /!
}

bool AudioManager::loadMusic(sf::String filename)
{
    bool initBuffer;
    if(!_filename.isEmpty())
        initBuffer = _buffer->loadFromFile(filename);
    else
        initBuffer = _buffer->loadFromFile(_filename);
    init();

    return initBuffer;
}

void AudioManager::init()
{
    _stream->load(*_buffer);
}

void AudioManager::play()
{
    if(_stream->getStatus() != SoundStream::Playing)
        _stream->play();
}

void AudioManager::pause()
{
    if(_stream->getStatus() != SoundStream::Paused)
        _stream->pause();
}

void AudioManager::stop()
{
    if(_stream->getStatus() != SoundStream::Stopped)
        _stream->stop();
}

void AudioManager::seek(sf::Time timeOffset)
{
    _stream->seek(timeOffset);
}
