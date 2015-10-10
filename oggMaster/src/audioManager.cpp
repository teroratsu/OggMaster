#include "../header/audioManager.h"

audioManager::audioManager()
{
    //ctor
}

audioManager::audioManager(sf::String filename)
{
    if(filename == "")
        this->filename_ = "./bin/Debug/music.ogg";
    else
        this->filename_ = filename;
}

audioManager::~audioManager()
{
    stream_.stop();
}

bool audioManager::loadMusic(sf::String filename)
{
    bool initBuffer;
    if(!filename_.isEmpty())
        initBuffer = buffer_.loadFromFile(filename);
    else
        initBuffer = buffer_.loadFromFile(this->filename_);
    init();

    return initBuffer;
}

void audioManager::init()
{
    stream_.load(buffer_);
}

void audioManager::play()
{
    if(stream_.getStatus() != SoundStream::Playing)
        stream_.play();
}

void audioManager::pause()
{
    if(stream_.getStatus() != SoundStream::Paused)
        stream_.pause();
}

void audioManager::stop()
{
    if(stream_.getStatus() != SoundStream::Stopped)
        stream_.stop();
}

void audioManager::seek(sf::Time timeOffset)
{
    stream_.seek(timeOffset);
}
