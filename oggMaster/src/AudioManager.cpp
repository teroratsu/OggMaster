#include "../header/AudioManager.h"

AudioManager::AudioManager()
{
    //ctor
    _stream.reset(new SoundStream()); //!< init the _stream object with a instance of a SoundStream class
    _buffer.reset(new sf::SoundBuffer()); //!< init the _buffer object with a instance of a sf::SoundBuffer class
    _wave.reset(new SoundWave()); //!< init the _wave object with a instance of a SoundWave class

    _stream->Attach(_wave.get());

    this->_filename = "./bin/Debug/music.ogg"; //default file loaded
}

AudioManager::AudioManager(sf::String filename)
{
    if(filename == "")
        this->_filename = "./bin/Debug/music.ogg"; //default file loaded
    else
        this->_filename = filename;

    _stream.reset(new SoundStream()); //!< init the _stream object with a instance of a SoundStream class
    _buffer.reset(new sf::SoundBuffer()); //!< init the _buffer object with a instance of a sf::SoundBuffer class
    _wave.reset(new SoundWave()); //!< init the _wave object with a instance of a SoundWave class

    _stream->Attach(_wave.get());
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

void AudioManager::test()
{
    const int BF_s = _wave->getBufferSize();
    float* test = _wave->getMagnitude();
    std::cout << "\nMagnitude : \n";
    for(int i=0; i<BF_s; i++)
        std::cout  << test[i] << "\t || \t";
}
