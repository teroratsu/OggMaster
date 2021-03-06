#include "../header/SoundStream.h"
#include "../header/Observer.h"

SoundStream::SoundStream(Observer* obs)
{
    Attach(obs);
    bufferEnd = false;
}

SoundStream::SoundStream()
{

}

SoundStream::~SoundStream()
{
    //dtor
}

/**
*   SoundStream : Public
**/

void SoundStream::load(const sf::SoundBuffer& buffer)
{
    // extract the audio samples from the sound buffer to our own container
    m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());

    // reset the current playing position
    m_currentSample = 0;

    // initialize the base class
    initialize(buffer.getChannelCount(), buffer.getSampleRate());

    bufferEnd = false;
}

bool SoundStream::isBufferEnd()
{
    return bufferEnd;
}

void SoundStream::seek(sf::Time timeOffset)
{
    setPlayingOffset(timeOffset);
}

void SoundStream::updateObs()
{
    Notify(getPlayingOffset());
}

/**
*   SoundStream : Private
**/

bool SoundStream::onGetData(Chunk& data)
{
    // number of samples to stream every time the function is called;
    // in a more robust implementation, it should be a fixed
    // amount of time rather than an arbitrary number of samples
    const int samplesToStream = 50000;
    bool r_;

    // set the pointer to the next audio samples to be played
    data.samples = &m_samples[m_currentSample];

    // have we reached the end of the sound?
    if (m_currentSample + samplesToStream <= m_samples.size())
    {
        // end not reached: stream the samples and continue
        data.sampleCount = samplesToStream;
        m_currentSample += samplesToStream;
        r_ = true;
    }
    else
    {
        // end of stream reached: stream the remaining samples and stop playback
        data.sampleCount = m_samples.size() - m_currentSample;
        m_currentSample = m_samples.size();
        r_ = false;
        bufferEnd = true;
    }
    if(r_)
        Notify(data, getSampleRate(), getChannelCount(), m_currentSample );//notify observer
    return r_;
}

void SoundStream::onSeek(sf::Time timeOffset)
{
    // compute the corresponding sample index according to the sample rate and channel count
    m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
}

/**
*      Observer pattern impementation
**/

#include <algorithm>


void SoundStream::Attach(Observer* o)
{
    _listObserver.push_back(o);
}
void SoundStream::Detach(Observer* o)
{
    _listObserver.erase(std::remove(_listObserver.begin(), _listObserver.end(), o), _listObserver.end());
}

void SoundStream::Notify(sf::SoundStream::Chunk& c, unsigned int s_r, unsigned int c_c, std::size_t m_s)
{
    for(std::vector<Observer*>::const_iterator iter = _listObserver.begin(); iter != _listObserver.end(); ++iter)
    {
        if(*iter != NULL)
        {
            (*iter)->update(c, s_r, c_c, m_s);
        }
    }
}

void SoundStream::Notify(sf::Time t)
{
    for(std::vector<Observer*>::const_iterator iter = _listObserver.begin(); iter != _listObserver.end(); ++iter)
    {
        if(*iter != NULL)
        {
            if(!bufferEnd)
                (*iter)->update(t);
        }
    }
}

sf::Time SoundStream::getPOffset(){ return getPlayingOffset();}

