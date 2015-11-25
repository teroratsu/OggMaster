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
    //! default ctor
    /*!
      \sa SoundWave()
    */
    SoundWave();//!< default ctor
    virtual ~SoundWave();//!< dtor
    //! return the BufferSize
    /*!
      \sa BUFFER_SIZE
      \return buffer size
    */
    int getBufferSize();
    //! init the soundwave data
    void init();

    float* getMagnitude();//!< return the magnitude array
    float* getPhase();//!< return the phase array
    float* getPower();//!< return the power array
    float getAvgPower();//!< return the avgPower
private:
    //! update with a new chunk of data
    /*!
      \param c chunk of data
      \param s_r Sample rate
      \param c_c Channel count
      \param s first sample of the chunk
      \sa update()
    */
    void update(sf::SoundStream::Chunk& c, unsigned int s_r, unsigned int c_c, std::size_t s); //!< update chunk
    //! update Soundwave with a given time offset
    /*!
      \param t time offset
      \sa update()
    */
    void update(sf::Time t); //!< force the refresh of the data
    //! clear the data in order to handle the update
    /*!
      \sa update()
    */
    void clearData();
    void conversionChunk(sf::SoundStream::Chunk&);

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
};

#endif // SOUNDWAVE_H
