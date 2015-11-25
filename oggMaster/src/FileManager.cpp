#include "../header/FileManager.h"

FileManager::FileManager()
{
    curFile = _fileMaker.getFile();//get default file
    _files.push_back(*curFile);//add the file to the list
    _curFileIndex = 0;//index of the first song
}

FileManager::~FileManager()
{
}

void FileManager::findAllFiles(const std::string& pathToDirectory, bool iterateSubFolders)
{
    boost::filesystem::path dirPath_(pathToDirectory);

    if(boost::filesystem::exists(dirPath_) && boost::filesystem::is_directory(dirPath_))//check if the path exist and is a directory
    {
        if ( !exists( dirPath_ ) )
            std::cout << dirPath_.string() << " doesn't exist" << std::endl;

        boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end

        for ( boost::filesystem::directory_iterator itr( dirPath_ );
            itr != end_itr;
            ++itr )
        {
            //std::cout << "FOUND \t" <<itr->path().string() << std::endl;
        if ( is_directory(itr->status()))
        {
            if(iterateSubFolders)
                findAllFiles(itr->path().string(), iterateSubFolders);
        }
        else
            addToVector(*itr);
        }
    }
}

File* FileManager::getFile(std::string file)//find using filename
{
    it = _files.begin() + _curFileIndex;
    it->initBuffer();
    it = std::find_if(_files.begin(), _files.end(),
             [file](const File & m) -> bool { return m.getFilename() == file; });
    if(it == _files.end())//check if the file exist (if the file has been found)
    {
        throw std::string("Error : " + file + " doesn't exist");
    }
    _curFileIndex = it - _files.begin();
    curFile = &(*it);
    return curFile;
}

void FileManager::preLoad()
{
    it = _files.begin() + _curFileIndex;//get the current file index
    if(++it == _files.end()){//if the next element doesn't exist
        it = _files.begin();
    }
    it->load();
}

File* FileManager::cur()
{
    it = _files.begin() + _curFileIndex;
    curFile = &(*it);
    return curFile;
}

File* FileManager::next()
{
    it = _files.begin() + _curFileIndex;//get the current file index
    it->initBuffer();
    if(++it == _files.end()){//if the next element doesn't exist
        it = _files.begin();
        _curFileIndex = 0;
    }
    else
        ++_curFileIndex;
    curFile = &(*it);
    return curFile;
}

File* FileManager::prev()
{
    it = _files.begin() + _curFileIndex;//get the current file index
    it->initBuffer();
    if(--it < _files.begin()){//if the next element doesn't exist
        it = _files.end()-1;
        _curFileIndex = _files.size()-1;//last element of the list
    }
    else
        --_curFileIndex;
    curFile = &(*it);
    return curFile;
}

void FileManager::deleteFile(std::string file)
{
    it = std::find_if(_files.begin(), _files.end(),
             [file](const File & m) -> bool { return m.getFilepath() == file; });
    if(it  != _files.end())
    {
        if(it->getFilepath() != curFile->getFilepath()){//must not be the current file
            if(_curFileIndex > it-_files.begin())
                --_curFileIndex;//on décale l'index en fonction du décalage réel du vector
            _files.erase(it);
        }
    }
    else
        std::cout << "Error : " << file << " doesn't exist" << std::endl;
}

void FileManager::fillVector(std::vector<File>& in_)
{
    in_ = _files;
}

void FileManager::addToVector(boost::filesystem::directory_entry entry)
{
    //verification over the entry to make sure it's not already in the map
    std::string file = entry.path().filename().string();
    file = file.substr(0,file.find_last_of('.'));
    //check if the file isn't already registered in the vector
    it = std::find_if(_files.begin(), _files.end(),
             [file](const File & m) -> bool { return m.getFilename() == file; });
    if(it == _files.end())
    {
        bool is_valid(false);
        std::string extension = entry.path().extension().string();
        extension = extension.substr(extension.find_last_of('.')+1);
        for(int i=0; i < NUMBER_OF_EXTENSION; i++)//verification over the extension
        {
            if(EXTENSIONS_VALIDES[i].compare(extension) == 0)
                is_valid = true;
        }
        if(is_valid)
        {
            _fileMaker.setProperties(entry);
            _files.push_back(*_fileMaker.getFile());
            //displayMap(); //just for test actually (maybe i've forgot about this comment :^)
        }
    }
}


