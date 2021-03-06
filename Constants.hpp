// =================================================================================
// Similar to #pragma once

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// =================================================================================



// =================================================================================
        // --------------- game.hpp ---------------

enum groupLabels : size_t
{
    groupMap,
    groupCollectibles,
    groupEnemies,
    groupPlayers,
    groupColliders
};

enum directions: size_t
{
        U,
        L,
        D,
        R
};

enum tags
{
        DEFAULT,
        PLAYER,
        ENEMY,
        COLLECTIBLE,
        TILE
};

#define WINDOW_SCALE         1
#define MAP_SCALE            1
#define ROWS_TO_SKIP        14

#define ROWS_TO_SKIP_PYTHON  2

#define MAZE_ROWS            20     //must be atleast 3
#define MAZE_COLUMNS         22  //must be atleast 3
#define DEFAULT_IMAGE_SIZE  32      /* CHANGE ONLY IF TILE SIZE AND IMAGE SIZE IS NOT 32 */
#define TILE_SIZE 32
#define BACKGROUND_COLOR    "Black" // Supported Colors -> "White" and "Black"
#define ANIMATION           false
#define OVERALL_SCALE       MAP_SCALE * WINDOW_SCALE
// =================================================================================



// =================================================================================
        // --------------- EntityComponentSystem.hpp ---------------

#define MAX_COMPONENTS 32 // For ECS.hpp file <- Max number of Components linked to an Entity
#define MAX_GROUPS     32 // For ECS.hpp file <- Group is a layer which will decide the Rendering Order
                          // So here, 32 are the Max number of Layers
// =================================================================================



// =================================================================================
        // --------------- KeyboardController.hpp ---------------

#define PLAYER_VELOCITY 1

// =================================================================================



// =================================================================================
        // --------------- SpriteComponent.hpp ---------------

#define FRAMES_FOR_IDLE     3
#define FRAMES_FOR_MOTION   8
#define ANIMATION_SPEED   100
// =================================================================================



// =================================================================================
        // --------------- TransformComponent.hpp ---------------

#define PLAYER_SPEED    1
#define SCREEN_WIDTH  MAZE_COLUMNS * DEFAULT_IMAGE_SIZE * WINDOW_SCALE
#define SCREEN_HEIGHT MAZE_ROWS * DEFAULT_IMAGE_SIZE    * WINDOW_SCALE
#define OFFSET 100 // For score
// #define SCREEN_WIDTH WINDOW_WIDTH
// #define SCREEN_HEIGHT WINDOW_HEIGHT
// =================================================================================



// =================================================================================
        // --------------- main.hpp ---------------
#define FRAMES_PER_SECOND 60
#define WINDOW_WIDTH      SCREEN_WIDTH
#define WINDOW_HEIGHT     SCREEN_HEIGHT

// =================================================================================

// =================================================================================
        // --------------- Kruskal_Maze.hpp ---------------
#define DEAD_END_REMOVAL 1            //value from 0 to 1

// =================================================================================


// =================================================================================
        // --------------- AIController.hpp ---------------
enum entitymodes: size_t
{
        IDLE, 
        BLINKY_CHASE,
        BLINKY_SCATTER,
        INKY_CHASE,
        INKY_SCATTER,
        PINKY_CHASE,
        PINKY_SCATTER,
        CLYDE_CHASE,
        CLYDE_SCATTER
};

// =================================================================================

#endif