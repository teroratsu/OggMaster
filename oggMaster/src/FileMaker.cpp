#include "../header/FileMaker.h"

File* FileMaker::getFile()
{
    return new File(_file);
}
void FileMaker::setProperties(boost::filesystem::directory_entry path)
{
    _file.setProperties(path);
}

FileMaker::FileMaker(): _file(DEFAULT_FILE)
{
}
