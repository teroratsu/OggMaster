#include "../header/AudioManager.h"

AudioManager::AudioManager()
{
    _allowUpdateObs = false;
    _stream.reset(new SoundStream()); //!< init the _stream object with a instance of a SoundStream class
    _buffer = new sf::SoundBuffer(); //!< init the _buffer object with a instance of a sf::SoundBuffer class
    _wave.reset(new SoundWave()); //!< init the _wave object with a instance of a SoundWave class
    _fManager.reset(new FileManager());
    _curFile = _fManager->cur();
    loadBuffer();

    _volume = 60;
    _stream->setVolume(_volume);

    _stream->Attach(_wave.get());
}

AudioManager::~AudioManager()
{
    _stream->stop(); //!< The audio buffer must be stopped before destroying the actual AudioManager object /!
}

void AudioManager::init()
{
    _stream->load(*_buffer);
    _wave->init();//clear inner data
    _allowUpdateObs = true;
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

void AudioManager::seek(const float& t_)
{
    if(_stream->getStatus() == SoundStream::Stopped)
        play();
    _stream->seek(sf::Time(t_ * _buffer->getDuration()));
}

void AudioManager::setVolume(const float& v_)
{
    _stream->setVolume(v_*100);
}

float AudioManager::getVolume()
{
    return _stream->getVolume()/100;
}

void AudioManager::update()
{
    if(_stream->getStatus() == SoundStream::Playing){
        const int BF_s = _wave->getBufferSize();
        if(_allowUpdateObs)
            _stream->updateObs();
    }
    if(_stream->getStatus() == SoundStream::Stopped)
    {
        if(_stream->isBufferEnd())
            next();
    }
    //!< TODO implement pre-load function
}

void AudioManager::loadMusic(std::string f_)
{
    _allowUpdateObs = false;
    stop();//stop the actual buffer
    try{_curFile = _fManager->getFile(f_);}
    catch(const std::string& e_){
        std::cout << e_ << std::endl;
    }
    loadBuffer();
}

void AudioManager::loadMusicFromFolder(std::string s, bool i)
{
    _fManager->findAllFiles(s,i);
    stop();
    _curFile = _fManager->getFile(_fManager->cur()->getFilename());
    loadBuffer();
}

void AudioManager::getAllFiles(std::vector<File>& in_)
{
    pause();
    _fManager->fillVector(in_);
    play();
}

void AudioManager::next()
{
    _allowUpdateObs = false;
    stop();//stop the actual buffer
    _curFile = _fManager->next();
    loadBuffer();
    //std::cout << _curFile->getBuffer()->getDuration().asSeconds() << std::endl;
    play();
}

void AudioManager::prev()
{
    _allowUpdateObs = false;
    stop();//stop the actual buffer
    _curFile = _fManager->prev();
    loadBuffer();
    //std::cout << _curFile->getBuffer()->getDuration().asSeconds() << std::endl;
    play();
}

void AudioManager::loadBuffer()
{
    if(!_curFile->isLoaded())//check if loaded
        _curFile->load();
    _buffer = _curFile->getBuffer();
    init();
}

/*void AudioManager::fillFileMap(std::map<std::string, File* >&)
{
    //!< TODO implement fill function for gui
}*/


std::string AudioManager::getDuration(){
     sf::Time cur = _stream->getPOffset();
     sf::Time tot = _buffer->getDuration();
     std::ostringstream os;
     std::string cur_sec, tot_sec;
     /* add a 0 if number of seconds is < 10 */
     ((int)cur.asSeconds()%60 < 10) ? cur_sec = std::string("0" + std::to_string((int)cur.asSeconds()%60)) : cur_sec = std::to_string((int)cur.asSeconds()%60);
     ((int)tot.asSeconds()%60 < 10) ? tot_sec = std::string("0" + std::to_string((int)tot.asSeconds()%60)) : tot_sec = std::to_string((int)tot.asSeconds()%60);
     os << (int)cur.asSeconds()/60 << ":" << cur_sec << " / " << (int)tot.asSeconds()/60 << ":" << tot_sec;
     return os.str();
}

float AudioManager::getDurationP()
{
    return _stream->getPOffset().asSeconds()/_buffer->getDuration().asSeconds();
}

sf::SoundSource::Status AudioManager::getStatus()
{
    return _stream->getStatus();
}

float* AudioManager::getSoundwave()
{
    return _wave->getMagnitude();
}

float* AudioManager::getPower()
{
    return _wave->getPower();
}

float* AudioManager::getPhase()
{
    return _wave->getPhase();
}

float AudioManager::getAvgPower()
{
    return _wave->getAvgPower();
}

std::string AudioManager::getCurPlayingSong() const
{
    return _fManager->cur()->getFilename();
}

