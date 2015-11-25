#include <iostream>
#include "../header/IHM.h"

int main(int argc, char* argv[])
{
    /*sf::String filename;
    if(argc > 1)
    {
        filename = argv[1];
        filename.replace("\\","/");
    }
    IHM ihm(filename);*/
    IHM ihm;
    ihm.Run();

    return 0;
}
