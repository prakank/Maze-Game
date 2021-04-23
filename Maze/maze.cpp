#include "header.hpp"

class Maze{

private:
    SDL_Window   *Maze_Window   = NULL;
    SDL_Surface  *Maze_Surface  = NULL;
    SDL_Renderer *Maze_Renderer = NULL;
    SDL_Rect gridCursor = {
        .w = CELL_WIDTH,
        .h = CELL_HEIGHT,
    };
    SDL_Rect gridCell = {
        .w = CELL_WIDTH,
        .h = CELL_HEIGHT,
    };
    bool Visited[ROWS][COLUMNS];
    stack< pii > cells;
    vector<vector<pii>> Neighbours;
    

    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_color = {0, 255, 0, 255}; // Green
    SDL_Color grid_cell_color = {255, 255, 255, 255}; // White

public:    

    bool init(){
        bool flag = true;
        
        for(int i=0;i < ROWS;i++)for(int j=0;j<COLUMNS;j++)Visited[i][j] = false;
        Neighbours.resize(ROWS*COLUMNS);

        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            USER_ERROR_SDL("Initialize SDL");
            flag = false;
        }
        if( SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &Maze_Window, &Maze_Renderer) < 0){
            USER_ERROR_SDL("Create Window and Renderer");
            flag = false;
        }
        SDL_SetWindowTitle(Maze_Window, "Maze");        
        return flag;
    }

    bool loadMedia(){
        bool flag = true;
        return flag;
    }

    void close(){
        SDL_Surface* surf = SDL_GetWindowSurface(Maze_Window);
        SDL_SaveBMP(surf, "Image");
        SDL_DestroyRenderer(Maze_Renderer);
        SDL_DestroyWindow(Maze_Window);
        SDL_Quit();
    }

    void generate(){
        
        
        if(!init())USER_ERROR_SDL("Unable to initialize");
        else{
            if(!loadMedia())USER_ERROR_SDL("Unable to Load Media");
            else{

                int i=0;
                int y = rand() % ROWS;
                int x = rand() % COLUMNS;
                cells.push(mp(x,y));
                Visited[x][y] = true;

                // d2(x,y);

                while( i < ROWS*COLUMNS ){
                    if(cells.empty())break;
                    pii x = cells.top();

                    int rownumber = x.first;
                    int columnnumber = x.second;
                    // d2(rownumber,columnnumber);
                    
                    vector< pii > temp;
                    if(rownumber+1 < ROWS && !Visited[rownumber+1][columnnumber])temp.pb(mp(rownumber+1,columnnumber));
                    if(rownumber-1 >= 0 && !Visited[rownumber-1][columnnumber])temp.pb(mp(rownumber-1,columnnumber));
                    if(columnnumber+1 < COLUMNS && !Visited[rownumber][columnnumber+1])temp.pb(mp(rownumber,columnnumber+1));
                    if(columnnumber-1 >= 0 && !Visited[rownumber][columnnumber-1])temp.pb(mp(rownumber,columnnumber-1));

                    // if(rownumber==0 && columnnumber==0){
                    //     if(Visited[rownumber+1][columnnumber] == true)d3("YES",rownumber+1,columnnumber);
                    //     if(Visited[rownumber][columnnumber+1] == true)d3("YES",rownumber,columnnumber+1);
                    //     // cout << ;
                    //     // cout << Visited[rownumber][columnnumber+1] == true;
                    // }
                    
                    if(temp.size()==0){
                        if(cells.empty()){break;}
                        cells.pop();
                        continue;
                    }
                    else{                        
                        pii y = temp[rand() % temp.size()];
                        cells.push(y);
                        Visited[y.first][y.second] = true;

                        // if(rownumber==0 && columnnumber==0){
                        //     cout << "DEB  ";
                        //     cout << cells.top().first << ", " << cells.top().second << endl;
                        //     d2(temp[0].first, temp[1].first);
                        // }

                        int ind1 = rownumber*COLUMNS + columnnumber;
                        int ind2 = y.first*COLUMNS + y.second;
                        
                        if( ( y.first == rownumber+1) || (y.second == columnnumber+1) )Neighbours[ind1].pb(y);
                        else Neighbours[ind2].pb(x);                        
                    }

                    SDL_SetRenderDrawColor(Maze_Renderer, grid_background.r, grid_background.b, grid_background.g, grid_background.a);
                    SDL_RenderClear(Maze_Renderer);

                    
                    SDL_SetRenderDrawColor(Maze_Renderer, grid_cell_color.r, grid_cell_color.b, grid_cell_color.g, grid_cell_color.a);
                    for(int i=0;i<ROWS;i++){
                        for(int j=0;j<COLUMNS;j++){
                            if(Visited[i][j]){
                                gridCell.y = i*CELL_HEIGHT;
                                gridCell.x = j*CELL_WIDTH;
                                SDL_RenderFillRect(Maze_Renderer, &gridCell);
                            }
                        }
                    }
                    SDL_RenderSetScale(Maze_Renderer,1,1);

                    SDL_SetRenderDrawColor(Maze_Renderer, grid_line_color.r, grid_line_color.g,grid_line_color.b, grid_line_color.a);

                    for(int i=0;i<=WINDOW_WIDTH;i+=CELL_WIDTH){
                        SDL_RenderDrawLine(Maze_Renderer, i, 0, i, WINDOW_HEIGHT);
                    }

                    for(int i=0;i<=WINDOW_HEIGHT;i+=CELL_HEIGHT){
                        SDL_RenderDrawLine(Maze_Renderer, 0, i, WINDOW_WIDTH, i);
                    }
                    
                    SDL_SetRenderDrawColor(Maze_Renderer, grid_cell_color.r, grid_cell_color.b, grid_cell_color.g, grid_cell_color.a);
                    
                    for(int k=0;k<Neighbours.size();k++){
                        
                        int row = k/COLUMNS;
                        int col = k%COLUMNS;

                        for(int p=0;p<Neighbours[k].size();p++){
                            // printp(Neighbours[k][p]);
                            SDL_RenderDrawLine(Maze_Renderer, (Neighbours[k][p].second)*CELL_WIDTH, (Neighbours[k][p].first)*CELL_WIDTH, (col+1)*CELL_WIDTH, (row+1)*CELL_WIDTH);
                        }
                    }
                    // cout << "\n\n";


                    SDL_SetRenderDrawColor(Maze_Renderer, grid_cursor_color.r,grid_cursor_color.g,grid_cursor_color.b,grid_cursor_color.a);
                    gridCursor.y = cells.top().first*CELL_WIDTH;
                    gridCursor.x = cells.top().second*CELL_HEIGHT;
                    SDL_RenderFillRect(Maze_Renderer, &gridCursor);

                    SDL_RenderPresent(Maze_Renderer);

                    // SDL_Delay(2);
                    
                    i++;
                    
                }
                SDL_Delay(5000);
                close();
            }
        }
    }
};

int main(int argc, char* argv[]){
    Maze maze;
    maze.generate();
}