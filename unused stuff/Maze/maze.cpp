#include "header.hpp"

class Maze{

private:
    SDL_Window   *Maze_Window   = NULL;
    SDL_Surface  *Maze_Surface  = NULL;
    SDL_Renderer *Maze_Renderer = NULL;
    SDL_Texture  *Maze_Texture  = NULL;
    SDL_Texture  *Tank_Texture  = NULL;

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
    vector<vector<int>> Map_Matrix;
    

    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_color = {0, 255, 0, 255}; // Green
    SDL_Color grid_cell_color = {255, 255, 255, 255}; // White

public:    

    bool init(){
        bool flag = true;
        
        srand(time(0)); // For Different Maze
        for(int i=0;i < ROWS;i++)for(int j=0;j<COLUMNS;j++)Visited[i][j] = false;
        Neighbours.resize(ROWS*COLUMNS);
        Map_Matrix.resize(ROWS);
        // 0 -> Right and Down both blocked
        // 1 -> Down blocked
        // 2 -> Right Blocked
        // 3 -> None Blocked

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

    SDL_Texture* load_texture(SDL_Renderer *renderer, string path) {
        SDL_Surface *bmp = NULL;
        SDL_Texture *texture = NULL;
        bmp = IMG_Load(path.c_str());
        SDL_Rect stretchRect = {
                    .x = 0,
                    .y = 0,
                    .w = CELL_WIDTH,
                    .h = CELL_HEIGHT,
                };
        SDL_BlitScaled(bmp, NULL, bmp, &stretchRect);
        if(bmp == NULL){
            d1(path.c_str());
            USER_ERROR_SDL("IMAGE ");
            return NULL;
        }
        texture = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_FreeSurface(bmp);
        return texture;
    }

    void close(){
        SDL_Surface* surf = SDL_GetWindowSurface(Maze_Window);
        SDL_SaveBMP(surf, "Image");
        SDL_DestroyRenderer(Maze_Renderer);
        SDL_DestroyWindow(Maze_Window);
        SDL_Quit();
    }

    void Form_Matrix(){
        for(int k=0;k<Neighbours.size();k++){
            int row = k/COLUMNS;
            int col = k%COLUMNS;
            if(Neighbours[k].size() == 0)Map_Matrix[row].pb(0); // Both blocked
            else if(Neighbours[k].size() == 2)Map_Matrix[row].pb(3); // None blocked
            else{
                if(Neighbours[k][0].first == row + 1)Map_Matrix[row].pb(2); // Right blocked
                else Map_Matrix[row].pb(1); // Down blocked
            }
            if(col==0)d1("");
            d0(Map_Matrix[row][col]);            
        }
        d1("");
    }

    void set_background_texture(SDL_Renderer *Renderer){

        SDL_RenderClear(Renderer);

        SDL_SetRenderDrawColor(Renderer, grid_cell_color.r, grid_cell_color.b, grid_cell_color.g, grid_cell_color.a);
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLUMNS;j++){
                gridCell.y = i*CELL_HEIGHT;
                gridCell.x = j*CELL_WIDTH;
                SDL_RenderFillRect(Renderer, &gridCell);
            }
        }

        SDL_SetRenderDrawColor(Renderer, grid_line_color.r, grid_line_color.g,grid_line_color.b, grid_line_color.a);
        for(int i=0;i<=WINDOW_WIDTH;i+=CELL_WIDTH){
            SDL_RenderDrawLine(Renderer, i, 0, i, WINDOW_HEIGHT);
        }
        for(int i=0;i<=WINDOW_HEIGHT;i+=CELL_HEIGHT){
            SDL_RenderDrawLine(Renderer, 0, i, WINDOW_WIDTH, i);
        }


        SDL_SetRenderDrawColor(Renderer, grid_cell_color.r, grid_cell_color.b, grid_cell_color.g, grid_cell_color.a);
        for(int k=0;k<Neighbours.size();k++){                        
            int row = k/COLUMNS;
            int col = k%COLUMNS;
            for(int p=0;p<Neighbours[k].size();p++){
                SDL_RenderDrawLine(Renderer, (Neighbours[k][p].second)*CELL_WIDTH, (Neighbours[k][p].first)*CELL_WIDTH, (col+1)*CELL_WIDTH, (row+1)*CELL_WIDTH);
            }
        }
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

                    if(temp.size()==0){
                        if(cells.empty()){break;}
                        cells.pop();
                        continue;
                    }
                    else{                        
                        pii y = temp[rand() % temp.size()];
                        cells.push(y);
                        Visited[y.first][y.second] = true;

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
                    if( (i+2) < ROWS*COLUMNS){
                        // d0(i);
                        SDL_RenderFillRect(Maze_Renderer, &gridCursor);
                    }
                    // d1(i);

                    SDL_RenderPresent(Maze_Renderer);

                    // SDL_Delay(100);
                    
                    i++;
                    
                }
                set_background_texture(Maze_Renderer);
                
                SDL_Event e;
                int pos_x = rand() % COLUMNS;
                int pos_y = rand() % ROWS;

                SDL_Rect tank = {
                    .x = pos_x*CELL_WIDTH,
                    .y = pos_y*CELL_HEIGHT,
                    .w = CELL_WIDTH,
                    .h = CELL_HEIGHT,
                };

                Tank_Texture = load_texture(Maze_Renderer, "tank.bmp");
                SDL_RenderCopy(Maze_Renderer, Tank_Texture, NULL, &tank);
                SDL_RenderPresent(Maze_Renderer);
                Form_Matrix();
                
                bool quit = false;
                while(!quit){
                    if(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_QUIT){
                            close();
                            quit = true;
                        }
                        else if( e.type == SDL_KEYDOWN)
                        {
                            
                            // 0 -> Right and Down both blocked
                            // 1 -> Down blocked
                            // 2 -> Right Blocked
                            // 3 -> None Blocked

                            switch( e.key.keysym.sym )
                            {
                                case SDLK_UP:
                                    if(tank.y > 0 && Map_Matrix[(tank.y/CELL_WIDTH)-1][(tank.x/CELL_HEIGHT)] >= 2)tank.y-=CELL_HEIGHT;
                                    break;
                                case SDLK_DOWN:
                                    if(tank.y < WINDOW_WIDTH - CELL_WIDTH && Map_Matrix[tank.y/CELL_WIDTH][tank.x/CELL_HEIGHT] >= 2)tank.y+=CELL_HEIGHT;
                                    break;
                                case SDLK_LEFT:
                                    if(tank.x > 0 && Map_Matrix[(tank.y/CELL_WIDTH)][(tank.x/CELL_HEIGHT)-1]%2 == 1)tank.x-=CELL_WIDTH;
                                    break;
                                case SDLK_RIGHT:
                                    if(tank.x < WINDOW_HEIGHT - CELL_HEIGHT && Map_Matrix[tank.y/CELL_WIDTH][tank.x/CELL_HEIGHT]%2 == 1)tank.x+=CELL_WIDTH;
                                    break;
                                case SDLK_ESCAPE:
                                    close();
                                    SDL_Quit();
                                    quit = true;
                                    break;
                            }

                            set_background_texture(Maze_Renderer);
                            SDL_RenderCopy(Maze_Renderer, Tank_Texture, NULL, &tank);
                            SDL_RenderPresent(Maze_Renderer);
                            // d5(tank.x, tank.y, tank.x/CELL_WIDTH, tank.y/CELL_HEIGHT, Map_Matrix[tank.x/CELL_WIDTH][tank.y/CELL_HEIGHT]);
                        }
                    }
                    
                }
                // close();
            }
        }
    }
};

int main(int argc, char* argv[]){
    Maze maze;
    maze.generate();
}