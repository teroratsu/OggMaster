#ifndef SOUNDSTREAM_H
#define SOUNDSTREAM_H

#include <SFML/Audio.hpp> //sf::SoundStream
#include <vector>
#include <iostream>
#include <memory>
#include "Observer.h"

class SoundStream : public sf::SoundStream
{
public:
    SoundStream();//default ctor
    SoundStream(Observer*);//!< ctor to initialize vite a given module (SoundWave)
    virtual ~SoundStream();

    //! load a given buffer to the _stream
    /*!
      \param b buffer to load
      \sa sf::SoundStream sf::SoundBuffer
    */
    void load(const sf::SoundBuffer& b); //! load
    //! seek bufferto the desired time
    /*!
      \param t time offset
      \sa sf::Time
    */
    void seek(sf::Time t); //!< seek to the desired time according to the audio file duration

    //! return the playing offset
    /*!
      \return the playing offset
    */
    sf::Time getPOffset();

    void updateObs(); //!< notify Observer with time elasped
    bool isBufferEnd();//!< return true if the current buffer is fully played

    //! sub an Observer to the audio flux
    /*!
      \param o pointer to an Observer
    */
    void Attach(Observer* o);

    //! unsub an Observer to the audio flux
    /*!
      \param o pointer to an Observer
    */
    void Detach(Observer* o);

private:

    //! Notify observers with a new chunk of data
      /*!
      \param c chunk of data
      \param s_r Sample rate
      \param c_c Channel count
      \param s first sample of the chunk
      \sa Notify()
    */
    void Notify(sf::SoundStream::Chunk& c, unsigned int s_r, unsigned int c_c, std::size_t s);
    //! Notify Observers with a given time offset
    /*!
      \param t time offset
      \sa Notify()
    */
    void Notify(sf::Time t);

    std::vector<Observer*> _listObserver;

    std::vector<sf::Int16> m_samples; //! samples from the buffer
    std::size_t m_currentSample; //! current sample (the "to be played" one)
    bool bufferEnd;

    virtual bool onGetData(Chunk&);
    virtual void onSeek(sf::Time);
};

#endif // SOUNDSTREAM_H
