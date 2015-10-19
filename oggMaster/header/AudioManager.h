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

class AudioManager
{
    public:
        AudioManager(); //!< default ctor
        /**
           * ctor that initialize the AudioManager filename var with the desired audio file.
           * @param s path to the desired audio file.
           * @see AudioManager()
        */
        AudioManager(sf::String s); //!< ctor handling auto file assignment
        virtual ~AudioManager(); //!< default ctor

        /**
           * load the file (_filename) into the soundBuffer.
           * @param s : path to the desired audio file.
           * @return true if the file as been loaded correctly into the buffer
        */
        bool loadMusic(sf::String s = ""); //!< load the file (_filename) into the soundBuffer
        void play(); //!< play the buffer by calling the SoundStream::play() method
        void pause(); //!< pause reading buffer by calling the SoundStream::pause() method
        void stop(); //!< stop reading buffer by calling the SoundStream::stop() method
        /**
           * seek to the desired time by calling the SoundStream::seek() method.
           * @param t : sf::Time object to indicate the desired duration to start the buffer from.
        */
        void seek(sf::Time t); //!< seek to the desired time by calling the SoundStream::seek() method

        /**
           * Return a pointer to the SoundWave instance (usefull for graphic classes that use FFT data to display the audio spectrum).
           * @return a pointer to the SoundWave instance
        */
        void test();

    private:
        void init();//!< init Soundstream object with buffer data

        std::unique_ptr<SoundStream> _stream; //!< smart pointer to the SoundStream (in order to be shared with other classes)
        std::unique_ptr<SoundWave> _wave; //!< smart pointer to the SoundWave (in order to be shared with the IHM obj)
        std::unique_ptr<sf::SoundBuffer> _buffer; //!< smart pointer to the SoundBuffer (in order to be shared with SoundWave & SoundStream)
        sf::String _filename;

};

#endif // AUDIOMANAGER_H
