#include<iostream>
#include<vector>
#include<chrono>
#include<map>
#include<stack>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>


// PARAMETERS FOR USER

// #define SCREEN_WIDTH  640
// #define SCREEN_HEIGHT 480
#define ROWS           10
#define COLUMNS        10
#define CELL_WIDTH     35
#define CELL_HEIGHT    35


#define WINDOW_WIDTH   CELL_WIDTH*COLUMNS
#define WINDOW_HEIGHT  CELL_HEIGHT*ROWS
#define USER_ERROR_SDL(x) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"%s: %s", x, SDL_GetError())


// FOR DEBUGGING

#define d0(x)           cout<<(x)<<" "
#define d1(x)           cout<<(x)<<endl
#define d2(x,y)         cout<<(x)<<" "<<(y)<<endl
#define d3(x,y,z)       cout<<(x)<<" "<<(y)<<" "<<(z)<<endl
#define d4(a,b,c,d)     cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<endl
#define d5(a,b,c,d,e)   cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<endl
#define d6(a,b,c,d,e,f) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<" "<<(f)<<endl

// NOTATIONS
#define ff first                 
#define ss second 
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define printp(x) cout << x.ff << " " << x.ss << "\n"


using namespace std;
using namespace std::chrono;