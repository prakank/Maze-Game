#include "MazeGeneration.hpp"

MazeGeneration::MazeGeneration(int seed)
{
    for(int i=0 ; i < Rows; i++){
        for(int j=0; j < Columns; j++){
            Visited[i][j] = 0;
            for(int k = 0;k<4;k++){
                Neighbours[i][j][k] = false;
            }
        }
    }

    random_seed = seed;

    Generate();
    GenerateTileMap();
    WriteToText();

    
};

void MazeGeneration::PushIntoArray(pii x, pii y)
{
    int RowNumber = x.ff;
    int ColumnNumber = x.ss;

    // Neighbours[..][..]
    // D will be Down Neighbour
    // R will be Right Neighbour


    if(y.ff == x.ff+1 && y.ss == x.ss)         {Neighbours[x.ff][x.ss][2] = true; Neighbours[y.ff][y.ss][0] = true;}
    else if(y.ff == x.ff-1 && y.ss == x.ss)    {Neighbours[x.ff][x.ss][0] = true; Neighbours[y.ff][y.ss][2] = true;}
    else if(y.ss == x.ss+1 && y.ff == x.ff)    {Neighbours[x.ff][x.ss][3] = true; Neighbours[y.ff][y.ss][1] = true;}
    else if(y.ss == x.ss-1 && y.ff == x.ff)    {Neighbours[x.ff][x.ss][1] = true; Neighbours[y.ff][y.ss][3] = true;}
}

void MazeGeneration::Generate()
{
    srand(random_seed);
    startX = rand() % Rows;
    startY = rand() % Columns;
    cout<<"X, Y"<<startX<<" "<<startY<<"\n";
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
        cout<<"Point "<<y.ff<<" "<<y.ss<<"\n";
        cells.push(y);
        PushIntoArray(x,y);        
        cnt++;
    }

}

/*bool MazeGeneration::ContainsChar(int i, int j, std::string s)
{
    if(Neighbours[i][j].size() == 2)return true;
    return Neighbours[i][j] == s;
}*/

// Will use Visited array to store the TileMap
void MazeGeneration::GenerateTileMap()
{
    int tileId = -1;

    for(int i=0; i < Rows; i++){
        for(int j=0; j < Columns; j++){
            
            tileId = 8*Neighbours[i][j][0] + 4*Neighbours[i][j][1] + 2*Neighbours[i][j][2] + Neighbours[i][j][3];
            Visited[i][j] = tileId;
        }
    }
}

void MazeGeneration::WriteToText()
{
    std::string filename = "Maze_txtfile.txt";
    std::ofstream output(filename);
    if(output.is_open()) cout<<"\n\nJa\n\n";
    else cout<<"\n\nNein\n\n";


    for(int i=0; i< Rows; i++){
        for(int j=0;j < Columns; j++){
            output << Visited[i][j];
            if(j == Columns-1) output << "\n";
            else output << ",";
        }
    }
    output.close();
}

void MazeGeneration::MazeGenerator()
{
    
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
