#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "SoundStream.h"
#include "FileManager.h"
#include "SoundWave.h"
#include <memory>
#include <string>
#include <sstream>
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
        virtual ~AudioManager(); //!< default ctor

        /**
           * load the file (_filename) into the soundBuffer.
           * @param s : path to the desired audio file.
           * @return true if the file as been loaded correctly into the buffer
        */
        bool loadMusic(sf::String s); //!< load the file (_filename) into the soundBuffer
        void loadMusicFromFolder(std::string); //!< load the files in the FileManager according to the folder path
        void play(); //!< play the buffer by calling the SoundStream::play() method
        void pause(); //!< pause reading buffer by calling the SoundStream::pause() method
        void stop(); //!< stop reading buffer by calling the SoundStream::stop() method
        void next(); //!< play the next song
        void prev(); //!< play the previous song

        //void fillFileMap(std::map<std::string,File*>&); //!<map to fill

        /**
           * seek to the desired time by calling the SoundStream::seek() method.
           * @param t : sf::Time object to indicate the desired duration to start the buffer from.
        */
        void seek(sf::Time t); //!< seek to the desired time by calling the SoundStream::seek() method
        void seek(const float&);

        void setVolume(const float&);

        float* getSoundwave();
        float* getPower();
        float* getPhase();
        float getAvgPower();

        std::string getCurPlayingSong() const;

        /**
           * Update what need to be updated
        */
        void update();
        std::string getDuration();
        //!< get the duration percentage 0.0f to 1.0f
        float getDurationP();
        float getVolume();
        sf::SoundSource::Status getStatus();

    private:
        void init();//!< init Soundstream object with buffer data
        void loadBuffer();

        std::unique_ptr<SoundStream> _stream; //!< smart pointer to the SoundStream (in order to be shared with other classes)
        std::unique_ptr<SoundWave> _wave; //!< smart pointer to the SoundWave (in order to be shared with the IHM obj)
        sf::SoundBuffer* _buffer; //!< smart pointer to the SoundBuffer (in order to be shared with SoundWave & SoundStream)
        std::unique_ptr<FileManager> _fManager;
        bool _allowUpdateObs;

        File* _curFile;

        //sf::String _filename;

        //! < SETTINGS > //user preference

        float _volume;

};

#endif // AUDIOMANAGER_H
