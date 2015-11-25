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
    //! load files from given folder into the vector
    /*!
      \param pathToDirectory path to the directory where to search for files
      \param iterateSubFolders true if you want to iterate the sub folders
      \sa _files
    */
    void findAllFiles(const std::string& pathToDirectory, bool iterateSubFolders=false);
    //! return the desired file according to the input string
    /*!
      \param file file to get (based on the filename)
      \return the desired file according to the input
    */
    File* getFile(std::string file);
    File* cur();//!< return the current file
    File* next();//!< return the next file in the list
    File* prev();//!< return the previous file in the list

    void preLoad();//!< load the nextFile's buffer

    //! delete file
    /*!
      \param file file to delete (based on the filename)
    */
    void deleteFile(std::string file); //!< delete the given file
    //! fill the in_ vector with file list
    /*!
      \param in_ vector of File to fill
    */
    void fillVector(std::vector<File>& in_);//in_ = _files 

private:
    //! register a file to the file list
    /*!
      \param file file to add (directory_entry)
      \return the desired file according to the input
    */
    void addToVector(boost::filesystem::directory_entry file);

    FileMaker _fileMaker;
    std::vector<File> _files;
    std::vector<File>::iterator it;

    File* curFile;
    int _curFileIndex;

    const std::string EXTENSIONS_VALIDES[NUMBER_OF_EXTENSION] = {"ogg", "wav", "flac", "aiff", "au", "raw", "paf", "svx", "nist", "voc", "ircam", "w64", "mat4", "mat5", "pvf", "htk", "sds", "avr", "sd2", "caf", "wve", "mpc2k", "rf64"};
};

#endif // FILEMANAGER_H
