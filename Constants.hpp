// =================================================================================
// Similar to #pragma once

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// =================================================================================



// =================================================================================
        // --------------- game.hpp ---------------

#define WINDOW_SCALE        3
#define MAP_SCALE           1
#define OVERALL_SCALE       MAP_SCALE * WINDOW_SCALE
#define ROWS_TO_SKIP       10
#define MAZE_ROWS           8
#define MAZE_COLUMNS        8
#define DEFAULT_IMAGE_SIZE 32    /* CHANGE ONLY IF TILE SIZE AND IMAGE SIZE IS NOT 32 */
#define BACKGROUND_COLOR "White" // Supported Colors -> "White" and "Black"
#define ANIMATION        false
// =================================================================================



// =================================================================================
        // --------------- EntityComponentSystem.hpp ---------------

#define MAX_COMPONENTS 32 // For ECS.hpp file <- Max number of Components linked to an Entity
#define MAX_GROUPS     32 // For ECS.hpp file <- Group is a layer which will decide the Rendering Order
                          // So here, 32 are the Max number of Layers
// =================================================================================



// =================================================================================
        // --------------- KeyboardController.hpp ---------------

enum Velocity : int
{
    REVERSE_DIRECTION_VELOCITY = -1,
    SAME_DIRECTION_VELOCITY    =  1,
    ZERO_VELOCITY              =  0
};

// =================================================================================



// =================================================================================
        // --------------- SpriteComponent.hpp ---------------

#define FRAMES_FOR_IDLE     3
#define FRAMES_FOR_MOTION   8
#define ANIMATION_SPEED   100
// =================================================================================



// =================================================================================
        // --------------- TransformComponent.hpp ---------------

#define PLAYER_SPEED    5
#define SCREEN_WIDTH  MAZE_COLUMNS * DEFAULT_IMAGE_SIZE * WINDOW_SCALE
#define SCREEN_HEIGHT MAZE_ROWS * DEFAULT_IMAGE_SIZE    * WINDOW_SCALE
// #define SCREEN_WIDTH WINDOW_WIDTH
// #define SCREEN_HEIGHT WINDOW_HEIGHT
// =================================================================================



// =================================================================================
        // --------------- main.hpp ---------------
#define FRAMES_PER_SECOND 60
#define WINDOW_WIDTH      SCREEN_WIDTH
#define WINDOW_HEIGHT     SCREEN_HEIGHT

// =================================================================================


#endif