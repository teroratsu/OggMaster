#include "../header/SoundWave.h"

SoundWave::SoundWave()
{
    init();

}

SoundWave::~SoundWave()
{
}

void SoundWave::update(sf::SoundStream::Chunk& c)
{
    float avg_power = 0.0f;
    static int index = 0;

    if(index < NUM_WINDOWS)
        index += 1;
    else
        index = 0;

    conversionChunk(c);

    _fft.powerSpectrum(0,BUFFER_SIZE/2,_chunkf,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power); //!< gros test yolo.

    for (int j=1; j<BUFFER_SIZE/2; j++)
    {
        freq[index][j] = magnitude[j]; //!< fill the array with corresponding data from the magnitude array
    }
}

void SoundWave::conversionChunk(sf::SoundStream::Chunk& c)
{
    int sampleC = static_cast<int>(c.sampleCount);
    _chunkf = new float[sampleC];
    for(int i=0; i< sampleC; i++)
            _chunkf[i] = (float) c.samples[i] / std::numeric_limits<sf::Int16>::max(); // signed to unsigned
}

void SoundWave::init()
{
    for(int i=0; i < NUM_WINDOWS; i++)
    {
        for(int j=0; j < NUM_WINDOWS; j++)
        {
            freq[i][j] = 0;
        }
    }
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

