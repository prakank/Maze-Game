#ifndef MAZE_GENERATION_HPP
#define MAZE_GENERATION_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "../Constants.hpp"

#define pii std::pair<int,int>
#define mp std::make_pair
#define pb push_back
#define ff first
#define ss second

class MazeGeneration{

    public:
        // 20*25 Current dimensions
        static const int Rows    =    MAZE_ROWS;
        static const int Columns = MAZE_COLUMNS;
        int Visited[Rows][Columns];
        // Will use Visited array to store the TileMap
        
        std::string Neighbours[Rows][Columns];
        
        // Neighbours[..][..]
        // D will be Down Neighbour
        // R will be Right Neighbour

        int startX, startY;
        std::stack< pii > cells;

        MazeGeneration(); // Initialize Visited to 0
        
        void Generate();
        void PushIntoArray(pii x, pii y);
        void GenerateTileMap();
        bool ContainsChar(int i, int j, std::string s);
        void WriteToText();
        void MazeGenerator();

};

#endif  