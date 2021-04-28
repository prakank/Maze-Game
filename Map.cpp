#include "Map.hpp"
#include "game.hpp"
#include "Constants.hpp"
#include <fstream>
#include<boost/algorithm/string.hpp>
#include<boost/format.hpp> 

Map::Map(){

}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    int tile;
    string out;
    ifstream read(path);

    int MapTileArray[sizeX][sizeY];
    int t=0;
    while(getline(read, out))
    {   
        vector<string> temp;
        boost::split(temp, out, boost::is_any_of(","));
        for(int p=0;p<temp.size();p++)MapTileArray[t][p] = stoi(temp[p]);
        t++;
    }

    for(int x = 0; x < sizeX; x++){
        for(int y = 0; y < sizeY; y++){
            
            tile = MapTileArray[x][y];
            Game::AddTile(tile, x * DEFAULT_IMAGE_SIZE, y * DEFAULT_IMAGE_SIZE);
            // cout << tile << " ";
        }

        // cout << "\n";
    }

    // mapFile.close();

}
