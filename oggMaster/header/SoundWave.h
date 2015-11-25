#ifndef SOUNDWAVE_H
#define SOUNDWAVE_H

#include <iostream>
#include <memory>
#include <queue>
#include <inttypes.h>

#include "SFML/Audio.hpp"
#include "FFT.h"
#include "Observer.h"

#define BUFFER_SIZE 256

class SoundWave : public Observer
{
    public:
        SoundWave();
        //SoundWave(std::shared_ptr<SoundStream> buffer); //!< must be the default ctor
        virtual ~SoundWave();//!< dtor

        int getBufferSize();
        void init();
        float* getMagnitude();
        float* getPhase();
        float* getPower();
        float getAvgPower();
    private:
    void update(sf::SoundStream::Chunk&, unsigned int, unsigned int, std::size_t); //!< update chunk
    void update(sf::Time); //!< force the refresh of the data
    /**
           * Initialize the freq array.
           * @see SoundWave()
    */
    void clearData();
    void conversionChunk(sf::SoundStream::Chunk&);

    //std::shared_ptr<SoundStream> _stream; //!< audio stream to work with
    const int NB_CHUNKF_STORED_MAX; //! < Max number of chunkf needed (to compensate the offset)

    FFT _fft;
    std::queue<float*> chunkList;//!< list of the 3 chunk of data converted to float

    //float* _chunkf; //!< chunk of data converted to float
    unsigned int _sampleRate; //!< sample rate of the actual chunk (still don't know if it can vary over time)
    unsigned int _channelCount;
    std::size_t _bSample; //!< base sample to compute the other ones relatively to this one
    std::size_t _cSample; //!< The one to be compute;
    bool allowUpdate;

    float magnitude[BUFFER_SIZE/2]; //!< contain the magnitude data from buffer once _fft.powerSpectrum() method is called
    float phase[BUFFER_SIZE/2]; //!< contain the phase data from buffer once _fft.powerSpectrum() method is called
    float power[BUFFER_SIZE/2]; //!< contain the power data from buffer once _fft.powerSpectrum() method is called

    float avg_power;

    //float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    //float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
};

#endif // SOUNDWAVE_H
