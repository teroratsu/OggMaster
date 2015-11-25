#ifndef FILEMAKER_H
#define FILEMAKER_H

#include "File.h"
#include <boost/filesystem.hpp>

template <class T> class Prototype
{
public:
	//! dtor
    virtual ~Prototype(){}
    //! get an instance of a file object
    /*!
      \return a pointer to a new file object
    */
    virtual File* getFile() =0 ;
};

class FileMaker: public Prototype<File>
{
public:
	//! default ctor
    FileMaker();
    //! get an instance of a file object
    /*!
      \return a pointer to a new file object
    */
    virtual File* getFile();
    //! set the given properties to the File object to clone
    /*!
      \param path path to the directory_entry
    */
    virtual void setProperties(boost::filesystem::directory_entry path);
private:
    File _file;
};

#endif // FILEMAKER_H
