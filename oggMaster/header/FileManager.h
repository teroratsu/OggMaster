#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "FileMaker.h"
#include <iostream>
//#include <map>
#include <vector>
#include <algorithm>

#define NUMBER_OF_EXTENSION 23

class FileManager
{
public:
    FileManager();//ctor
    virtual ~FileManager();//dtor

    /**
    *   @param std::string : folder to iterate
    *   @param bool : true if you want to iterate the sub folders (false by default)
    **/
    void findAllFiles(const std::string& pathToDirectory, bool iterateSubFolders=false);
    /**
    *   @return File* : a pointer to the required file
    *   @param std::string : file required by user
    **/
    File* getFile(std::string file);
    File* cur() const;
    File* next();
    File* prev();

    void preLoad();

    void deleteFile(std::string file);

private:
    void addToVector(boost::filesystem::directory_entry);

    FileMaker _fileMaker;
    std::vector<File> _files;
    std::vector<File>::iterator it;

    File* curFile;
    int _curFileIndex;

    const std::string EXTENSIONS_VALIDES[NUMBER_OF_EXTENSION] = {"ogg", "wav", "flac", "aiff", "au", "raw", "paf", "svx", "nist", "voc", "ircam", "w64", "mat4", "mat5", "pvf", "htk", "sds", "avr", "sd2", "caf", "wve", "mpc2k", "rf64"};
};

#endif // FILEMANAGER_H
