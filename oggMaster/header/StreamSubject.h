#ifndef STREAMSUBJECT_H
#define STREAMSUBJECT_H

#include <vector>

#include "Observer.h"

class StreamSubject
{
public:
    void Attach(Observer*);
    void Detach(Observer*);
    void Notify(sf::SoundStream::Chunk&);
protected :
    std::vector<Observer*> _listObserver;
};

#endif // STREAMSUBJECT_H
