#ifndef FILE_H
#define FILE_H

#include <SFML/Audio.hpp>
#include <boost/filesystem.hpp>

#define DEFAULT_FILE "./playMe/Musique.ogg"

class File
{
public:
    //! ctor taking a directory_entry as a parameter
    /*!
      \param path directory_entry path (filepath).
      \sa FileSystem
      \sa File()
    */
    File(boost::filesystem::directory_entry path);
    //! ctor taking a string as a parameter
    /*!
      \param path file path
      \sa File()
    */
    File(std::string path);
    //! copy ctor
    /*!
      \param f File to copy
      \sa File()
    */
    File(const File& f);
    ~File();//!< default dtor

    //! change properties of the file (his path, filename of extension)
    /*!
      \param path directory_entry path (filepath).
    */
    void setProperties(boost::filesystem::directory_entry path);

    //! load the buffer
    /*!
      \sa _buffer
    */
    void load();

    //! return true if the buffer is already loaded
    /*!
      \return true if the buffer is already loaded
      \sa _buffer
    */
    bool isLoaded() const;

    //! init the internal buffer
    /*!
      \sa load() and isLoaded()
    */
    void initBuffer();

    sf::SoundBuffer* getBuffer() const; //!< return a pointer to the buffer
    std::string getFilename() const; //!< return the File name
    std::string getFiletype() const; //!< return the File type (based on his extension)
    std::string getFilepath() const; //!< return the File path

private:
    std::string _filename, _filetype, _filepath;
    sf::SoundBuffer* _buffer;
    bool loaded;//true si chargée
};

#endif // FILE_H
