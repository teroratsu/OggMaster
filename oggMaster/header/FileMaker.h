#ifndef FILEMAKER_H
#define FILEMAKER_H

#include "File.h"
#include <boost/filesystem.hpp>

template <class T> class Prototype
{
public:
    virtual ~Prototype(){}
    virtual File* getFile() =0 ;
};

class FileMaker: public Prototype<File>
{
public:
    FileMaker();
    virtual File* getFile();
    virtual void setProperties(boost::filesystem::directory_entry path);
private:
    File _file;
};

#endif // FILEMAKER_H
