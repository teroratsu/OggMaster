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
    *   This is the main class to handle audio files :
    *   - load files using loadMusic : with as parameter the path to the required file.
    *   - play, pause & stop (& seek) calling SoundStream inner methods. (The SoundStream is initialized once loadMusic method is called).
    */

class AudioManager
{

    public:
        AudioManager(); //!< default ctor
        virtual ~AudioManager(); //!< default dtor

        //! given a file name, load the wanted file from the FileManager
        /*!
          \param filename name of the file to load.
          \sa _fmanager and loadMusicFromFolder()
        */
        void loadMusic(std::string fileName); //< load the file (_filename) into the soundBuffer
        //! given a folder path and a boolean, call the associated method of the FileManager
        /*!
          \param folderPath path to the folder to load the files from.
          \param itSubFolders while true, allow tht FileManager to iterate the sub folders in order to load files.
          \sa _fmanager and loadMusic()
        */
        void loadMusicFromFolder(std::string folderPath, bool itSubFolders = true); //< load the files in the FileManager according to the folder path
        //! play the audio file loaded
        /*!
          \sa _stream
        */
        void play(); //!< play the buffer by calling the SoundStream::play() method

        //! pause the audio file loaded
        /*!
          \sa _stream
        */
        void pause(); //!< pause reading buffer by calling the SoundStream::pause() method

        //! stop the audio file loaded
        /*!
          \sa _stream
        */
        void stop(); //!< stop reading buffer by calling the SoundStream::stop() method

        //! play the next audio file
        /*!
          \sa _stream and _fmanager
        */
        void next(); //!< play the next song

        //! play the previous audio file
        /*!
          \sa _stream and _fmanager
        */
        void prev(); //!< play the previous song

        //! seek to the desired time by calling the SoundStream::seek() method.
        /*!
          \param t : sf::Time object to indicate the desired duration to start the buffer from.
          \sa _stream
        */
        void seek(sf::Time t); //!< seek to the desired time by calling the SoundStream::seek() method

        //! seek to the desired time by calling the SoundStream::seek() method (after a little conversion from float to sf::Time).
        /*!
          \param t : float, 0 to 1 reprensenting the offset ratio you want to seek to
          \sa _stream and _buffer
        */
        void seek(const float& t);

        //! change the volume in the _stream properties
        /*!
          \param t : float, 0 to 100 % of the max volume, 0 to mute
          \sa _stream and _buffer
        */
        void setVolume(const float& t);

        float* getSoundwave(); //!< return the magnitude (the main float array for visualization routine)
        float* getPower(); //!< return the power array whiwh can be usefull for certain stuff
        float* getPhase(); //!< return the phase (not often use but can be usefull for some kind of audio processing)
        float getAvgPower(); //!< return the average power, pretty usefull for bass detection

        //! return the current file name
        /*!
          \return the current file name
          \sa _curFile
        */
        std::string getCurPlayingSong() const;

        //! fill the given array with the _fmanager file list
        /*!
          \param v : vector of files to fill
          \sa _fmanager
        */
        void getAllFiles(std::vector<File>& v);

        //! public update mainly for moduleslike SoundWave
        /*!
          \sa _wave and _stream
        */
        void update();

        //! return the actual duration as a string
        /*!
          \return actual duration string
          \sa _stream and _buffer
        */
        std::string getDuration();

        //! return the actual duration as a float
        /*!
          \return duration as a float which value is between 0 and 1
          \sa _stream and _buffer
        */
        float getDurationP();

        //! return the current volume
        /*!
          \return the current volume of the stream
          \sa _stream
        */
        float getVolume();

        //! return the status of the stream
        /*!
          \return the scurrent status of the stream
          \sa _stream
        */
        sf::SoundSource::Status getStatus();

    private:
        //! init the buffer and the stream
        /*!
          \sa _stream and _buffer
        */
        void init();//!< init Soundstream object with buffer data
        //! change the volume in the _stream properties
        /*!
          \param t : float, 0 to 100 % of the max volume, 0 to mute
          \sa _stream and _buffer
        */
        void loadBuffer();

        std::unique_ptr<SoundStream> _stream; //!< smart pointer to the SoundStream (in order to be shared with other classes)
        std::unique_ptr<SoundWave> _wave; //!< smart pointer to the SoundWave (in order to be shared with the IHM obj)
        sf::SoundBuffer* _buffer; //!< pointer to the SoundBuffer (in order to be shared with SoundWave & SoundStream)
        std::unique_ptr<FileManager> _fManager; //!< smart pointer to the FileManager (in order to be shared with the IHM obj)
        bool _allowUpdateObs;

        File* _curFile;

        //sf::String _filename;

        //! < SETTINGS > //user preference

        float _volume;

};

#endif // AUDIOMANAGER_H
