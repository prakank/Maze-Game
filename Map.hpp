#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

class Map{

    public:
        Map();
        ~Map();
        static void LoadMap(std::string path, int sizeX, int sizeY);
    

};

#endif