#ifndef SOUNDWAVE_H
#define SOUNDWAVE_H

#include <iostream>
#include <memory>
#include "SFML/Audio.hpp"
#include "FFT.h"
#include "Observer.h"

#define BUFFER_SIZE 256
#define NUM_WINDOWS 80

class SoundWave : public Observer
{
    public:
        SoundWave();
        //SoundWave(std::shared_ptr<SoundStream> buffer); //!< must be the default ctor
        virtual ~SoundWave();

        int getBufferSize();
        float* getMagnitude();
        float* getPhase();
        float* getPower();
    private:
    void update(sf::SoundStream::Chunk&);
    /**
           * Initialize the freq array.
           * @see SoundWave()
    */
    void init();
    void conversionChunk(sf::SoundStream::Chunk&);

    //std::shared_ptr<SoundStream> _stream; //!< audio stream to work with

    FFT _fft;

    float* _chunkf; //!<

    float magnitude[BUFFER_SIZE]; //!< contain the magntiude data from buffer once _fft.powerSpectrum() method is called
    float phase[BUFFER_SIZE]; //!< contain the phase data from buffer once _fft.powerSpectrum() method is called
    float power[BUFFER_SIZE]; //!< contain the power data from buffer once _fft.powerSpectrum() method is called

    float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
};

#endif // SOUNDWAVE_H
