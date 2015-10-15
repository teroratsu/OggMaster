#include "../header/SoundWave.h"
#include <math.h>

SoundWave::SoundWave()
{
    //ctor
    init();
}

SoundWave::SoundWave(std::shared_ptr<SoundStream> stream)
{
    _stream = stream;
    init();
}

SoundWave::~SoundWave()
{
    //dtor
}

void SoundWave::update()
{
    float avg_power = 0.0f;
    static int index = 0;

    if(index < NUM_WINDOWS)
        index += 1;
    else
        index = 0;

    conversionChunk(_stream->getLastChunk().samples, _stream->getLastChunk().sampleCount);

    _fft.powerSpectrum(0,BUFFER_SIZE/2,_chunkf,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power); //!< gros test yolo.

    for (int j=1; j<BUFFER_SIZE/2; j++)
    {
        freq[index][j] = magnitude[j]; //!< fill the array with corresponding data from the magnitude array
    }
}

void SoundWave::conversionChunk(const sf::Int16* samples, size_t sampleCount)
{
    int sampleC = static_cast<int>(sampleCount);
    _chunkf = new float[sampleC];
    for(int i=0; i< sampleC; i++)
            _chunkf[i] = (float) samples[i] / std::numeric_limits<sf::Int16>::max(); // signed to unsigned
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
