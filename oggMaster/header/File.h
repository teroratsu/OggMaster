#ifndef FILE_H
#define FILE_H

#include <SFML/Audio.hpp>
#include <boost/filesystem.hpp>

#define DEFAULT_FILE "./playMe/Musique.ogg"

class File
{
public:
    File(boost::filesystem::directory_entry path);
    File(std::string path);
    File(const File&);
    ~File();

    void setProperties(boost::filesystem::directory_entry path);

    void load();
    bool isLoaded() const;
    void initBuffer();

    sf::SoundBuffer* getBuffer() const;
    std::string getFilename() const;
    std::string getFiletype() const;
    std::string getFilepath() const;

private:
    std::string _filename, _filetype, _filepath;
    sf::SoundBuffer* _buffer;
    bool loaded;//true si chargée
};

#endif // FILE_H
