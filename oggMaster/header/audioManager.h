#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "SoundStream.h"
#include "SoundWave.h"
#include <memory>
#include "FFT.h"

    /*! \brief  The AudioManager handle basic operations such play, pause or stop a soundStream.
    *           The audio data are stored in the buffer and are being use by SoundStream to do all the hard work.
    *
    *   This is the main class for handling audio files :
    *   - load files using loadMusic : with as parameter the path to the required file.
    *   - play, pause & stop (& seek) calling SoundStream inner methods. (The SoundStream is initialized once loadMusic method is called).
    *   - get the FFT data by using the inner methods from the SoundWave handler
    */

class audioManager
{
    public:
        audioManager(); //!< default ctor
        audioManager(sf::String); //!< ctor handling auto file assignment
        virtual ~audioManager(); //!< default ctor

        bool loadMusic(sf::String = ""); //!< load the file (_filename) into the soundBuffer
        void play(); //!< play the buffer by calling the SoundStream::play() method
        void pause(); //!< pause reading buffer by calling the SoundStream::pause() method
        void stop(); //!< stop reading buffer by calling the SoundStream::stop() method
        void seek(sf::Time); //!< seek to the desired time by calling the SoundStream::seek() method

        std::shared_ptr<SoundWave> getSoundWave(); //!< give the IHM class an access to soundWave public methods

    private:
        void init();//init Soundstream object with buffer data

        std::shared_ptr<SoundStream> _stream; //!< smart pointer to the SoundStream (in order to be shared with other classes)
        std::shared_ptr<SoundWave> _wave; //!< smart pointer to the SoundWave (in order to be shared with the IHM obj)
        std::shared_ptr<sf::SoundBuffer> _buffer; //!< smart pointer to the SoundBuffer (in order to be shared with SoundWave & SoundStream)
        sf::String _filename;

};

#endif // AUDIOMANAGER_H
