#include "MazeGeneration.hpp"
#include <fstream>

MazeGeneration::MazeGeneration()
{
    for(int i=0 ; i < Rows; i++){
        for(int j=0; j < Columns; j++){
            Visited[i][j] = 0;
            Neighbours[i][j] = "";
            Neighbours[i][j] = "";
        }
    }
    
}

void MazeGeneration::PushIntoArray(pii x, pii y)
{
    int RowNumber = x.ff;
    int ColumnNumber = x.ss;

    // Neighbours[..][..]
    // D will be Down Neighbour
    // R will be Right Neighbour


    if(y.ff == RowNumber+1)         Neighbours[x.ff][x.ss] += "D";
    else if(y.ff == RowNumber-1)    Neighbours[y.ff][y.ss] += "D";
    else if(y.ss == ColumnNumber+1) Neighbours[x.ff][x.ss] += "R";
    else                            Neighbours[y.ff][y.ss] += "R";
}

void MazeGeneration::Generate()
{
    srand(time(0));
    startX = rand() % Rows;
    startY = rand() % Columns;
    cells.push(mp(startX,startY));
    Visited[startX][startY] = 1;
    int cnt = 1;

    while(cnt < Rows*Columns)
    {
        if(cells.empty())break;        
        pii x = cells.top();
        int RowNumber = x.ff;
        int ColumnNumber = x.ss;

        std::vector<pii> temp; // Checking if any neighbour is unvisited
        if(RowNumber+1 < Rows       && Visited[RowNumber+1][ColumnNumber] == 0)temp.pb(mp(RowNumber+1,ColumnNumber));
        if(RowNumber-1 >= 0         && Visited[RowNumber-1][ColumnNumber] == 0)temp.pb(mp(RowNumber-1,ColumnNumber));
        if(ColumnNumber+1 < Columns && Visited[RowNumber][ColumnNumber+1] == 0)temp.pb(mp(RowNumber,ColumnNumber+1));
        if(ColumnNumber-1 >= 0      && Visited[RowNumber][ColumnNumber-1] == 0)temp.pb(mp(RowNumber,ColumnNumber-1)); 
        
        if(temp.size() == 0)
        {
            cells.pop();
            continue;
        }
        pii y = temp[rand() % temp.size()];
        Visited[y.ff][y.ss] = 1;
        cells.push(y);
        PushIntoArray(x,y);        
        cnt++;
    }

}

bool MazeGeneration::ContainsChar(int i, int j, std::string s)
{
    if(Neighbours[i][j].size() == 2)return true;
    return Neighbours[i][j] == s;
}

// Will use Visited array to store the TileMap
void MazeGeneration::GenerateTileMap()
{
    int tileId = -1;

    for(int i=0; i < Rows; i++){
        for(int j=0; j < Columns; j++){
            
            if(Neighbours[i][j].size() == 2 && 
               i > 0 && ContainsChar(i-1,j,"D") &&
               j > 0 && ContainsChar(i,j-1,"R") 
            )tileId = 0;
            
            else if(Neighbours[i][j].size() == 2 &&
                    j > 0 && ContainsChar(i,j-1,"R")
                )tileId = 1;
            
            else if(i > 0 && ContainsChar(i-1,j,"D") &&
                    j > 0 && ContainsChar(i,j-1,"R") &&
                    Neighbours[i][j] == "D"
               ) tileId = 2;

            else if(i > 0 && ContainsChar(i-1,j,"D") &&
                    j > 0 && ContainsChar(i,j-1,"R") &&
                    Neighbours[i][j] == "R"
               ) tileId = 3;

            else if(Neighbours[i][j].size() == 2 &&
                    i > 0 && ContainsChar(i-1,j,"D")
                )tileId = 4;

            else if(Neighbours[i][j] == "D" &&
                    j > 0 && ContainsChar(i,j-1,"R")
                )tileId = 5;
            
            else if(Neighbours[i][j] == "R" &&
                    j > 0 && ContainsChar(i,j-1,"R")
                )tileId = 6;

            else if(Neighbours[i][j].size() == 2)
                 tileId = 7;

            else if(i > 0 && ContainsChar(i-1,j,"D") &&
                    j > 0 && ContainsChar(i,j-1,"R") 
                )tileId = 8;

            else if(Neighbours[i][j] == "D" &&
                    i > 0 && ContainsChar(i-1,j,"D")
                )tileId = 9;

            else if(Neighbours[i][j] == "R" &&
                    i > 0 && ContainsChar(i-1,j,"D")
                )tileId = 10;

            else if(j > 0 && ContainsChar(i,j-1,"R")
                )tileId = 11;
            
            else if(Neighbours[i][j] == "D")
                 tileId = 12;
            
            else if(Neighbours[i][j] == "R")
                 tileId = 13;

            else if( i > 0 && ContainsChar(i-1,j,"D") )
                 tileId = 14;

            else 
                {
                    tileId = 15;
                    std::cout << "ERROR\n";
                }
            Visited[i][j] = tileId;
        }
    }
}

void MazeGeneration::WriteToText()
{
    std::string filename = "assets/Maze.txt";
    std::ofstream output(filename);
    
    for(int i=0; i< Rows; i++){
        for(int j=0;j < Columns; j++){
            output << Visited[i][j];
            if(j == Columns-1)output << "\n";
            else output << ",";
        }
    }
    output.close();
}

void MazeGeneration::MazeGenerator()
{
    Generate();
    GenerateTileMap();
    WriteToText();
    // std::cout << "Hey";
}

// int main(){
//     MazeGeneration *m = new MazeGeneration();
//     m->Generate();
//     m->GenerateTileMap();
//     m->WriteToText();
//     // for(int i=0; i< m->Rows; i++){
//     //     for(int j=0; j< m->Columns; j++){
//     //         std::cout << m->Visited[i][j] << " ";
//     //     }
//     //     std::cout << std::endl;
//     // }
//     return 0;
// }