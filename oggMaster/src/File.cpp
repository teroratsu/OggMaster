#include "../header/File.h"

File::File(boost::filesystem::directory_entry path){
    _filepath = path.path().string();
    _filename = path.path().filename().string();
    _filetype = _filename.substr(_filename.find_last_of('.')+1);
    _filename = _filename.substr(0,_filename.find_last_of('.'));

    _buffer   = new sf::SoundBuffer();

    loaded    = false;
}

File::File(std::string path)
{
    if(path.empty())
        path = DEFAULT_FILE;
    _filepath = path;
    _filename = path.substr(path.find_last_of('/')+1);
    _filename = _filename.substr(0,_filename.find_last_of('.'));
    _filetype = path.substr(path.find_last_of('.')+1);

    _buffer = new sf::SoundBuffer();

    loaded    = false;
}

File::File(const File& file){
    _filename   = file.getFilename();
    _filetype   = file.getFiletype();
    _filepath   = file.getFilepath();
    _buffer     = new sf::SoundBuffer();

    if(file.isLoaded())
        loaded  = true;
    else
        loaded  = false;
}

File::~File()
{
    //dtor
    //delete _buffer;
}

void File::load()
{
        if(!_buffer->loadFromFile(_filepath))
        {
            //error
        }
        else
            loaded = true;
}

bool File::isLoaded() const
{
    return loaded;
}

sf::SoundBuffer* File::getBuffer() const
{
    return _buffer;
}

void File::initBuffer()
{
    delete _buffer;
    _buffer = new sf::SoundBuffer();
    loaded = false;
}

void File::setProperties(boost::filesystem::directory_entry path)
{
    _filepath = path.path().string();
    _filename = path.path().filename().string();
    _filetype = _filename.substr(_filename.find_last_of('.')+1);
    _filename = _filename.substr(0,_filename.find_last_of('.'));
}

std::string File::getFilename() const
{
    return _filename;
}

std::string File::getFiletype() const
{
    return _filetype;
}

std::string File::getFilepath() const
{
    return _filepath;
}

