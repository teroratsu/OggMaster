#include "StreamSubject.h"
#include <algorithm>

void StreamSubject::Attach(Observer* o)
{
    _listObserver.push_back(o);
}
void StreamSubject::Detach(Observer* o)
{
    _listObserver.erase(std::remove(_listObserver.begin(), _listObserver.end(), o), _listObserver.end());
}

void StreamSubject::Notify(sf::SoundStream::Chunk& c)
{
    for(std::vector<Observer*>::const_iterator iter = _listObserver.begin(); iter != _listObserver.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->update(c);
        }
    }
}
