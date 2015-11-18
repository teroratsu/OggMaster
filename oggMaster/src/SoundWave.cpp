#include "../header/SoundWave.h"

SoundWave::SoundWave() : NB_CHUNKF_STORED_MAX(3)
{
    init();
}

SoundWave::~SoundWave()
{
}

void SoundWave::update(sf::Time c_s)
{
    _cSample = static_cast<std::size_t>(c_s.asSeconds() * _sampleRate * _channelCount) - ((int64_t)_bSample -3*50000); //!< -_bSample make it relatively to the Chunk
    //std::cout <<_cSample << std::endl; //there is 3 buffer before the one
    clear();
    if(_cSample >= 0 && _cSample < 50000)
        _fft.powerSpectrum(0,BUFFER_SIZE/2,&chunkList.front()[_cSample],BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power); //!< compute data
}

void SoundWave::update(sf::SoundStream::Chunk& c , unsigned int s_r, unsigned int c_c, std::size_t s)
{
    conversionChunk(c); //convert and store the chunk
    _sampleRate     = s_r;
    _channelCount   = c_c;
    _bSample        = s;
}

void SoundWave::conversionChunk(sf::SoundStream::Chunk& c)
{
    int sampleC = static_cast<int>(c.sampleCount);
    chunkList.push(new float[sampleC]);
    for(int i=0; i< sampleC; i++)
            chunkList.back()[i] = (float) c.samples[i] / std::numeric_limits<sf::Int16>::max(); // signed to unsigned
    allowUpdate = true;
    if(chunkList.size() > NB_CHUNKF_STORED_MAX)
    {
        chunkList.pop();
    }
}

void SoundWave::clear()
{
    for(int i=0; i < BUFFER_SIZE/2; i++)
    {
        magnitude[i] = 0;
        phase[i] = 0;
        power[i] = 0;
    }
    avg_power = 0.0f;
}

void SoundWave::init()
{
    std::queue<float*> empty;
    std::swap(chunkList,empty);//empty the queue
    _chunkf = nullptr;
    allowUpdate = false;
}

int SoundWave::getBufferSize()
{
    return BUFFER_SIZE;
}

float* SoundWave::getMagnitude()
{
    return magnitude;
}

float* SoundWave::getPhase()
{
    return phase;
}

float* SoundWave::getPower()
{
    return power;
}

float SoundWave::getAvgPower()
{
    return avg_power;
}


