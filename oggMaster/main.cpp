#include <iostream>
#include "IHM.h"

int main(int argc, char* argv[])
{
    sf::String filename;
    if(argc > 1)
    {
        filename = argv[1];
        filename.replace("\\","/");
    }
    IHM ihm(filename);
    ihm.Run();

    return 0;
}
