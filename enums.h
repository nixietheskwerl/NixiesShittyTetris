/**
 * @file enums.h
 */

#include <cstdint>

#ifndef ENUMS_H
#define ENUMS_H

enum GameState
{
    STATE_INIT,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAMEOVER
};

enum CollisionType
{
    FLOOR,
    WALL,
    PIECE,
    NONE
};

enum Direction
{
    LEFT,
    RIGHT,
    DOWN,
    ROTATION_LEFT,
    ROTATION_RIGHT
};

enum TetrominoType
{
    TETROMINO_I,
    TETROMINO_J,
    TETROMINO_L,
    TETROMINO_O,
    TETROMINO_S,
    TETROMINO_T,
    TETROMINO_Z,
    TETROMINO_NONE
};

enum settings
{
    SETTING_GRID_VISIBLE = true,
    SETTING_NEXT_PIECE_VISIBLE = true,
    SETTING_HOLD_PIECE_VISIBLE = true,
    SETTING_GHOST_PIECE_VISIBLE = true,
    SETTING_SOFT_DROP_ENABLED = true,
    SETTING_SOUND_ENABLED = true,
    SETTING_MUSIC_ENABLED = true,
    GRID_WIDTH = 10,
    GRID_HEIGHT = 20,
    BLOCK_SIZE_X = 30,
    BLOCK_SIZE_Y = 30,
    WINDOW_X_RESOLUTION = 800,
    WINDOW_Y_RESOLUTION = 800,
    GAME_OFFSET_X = 100,
    GAME_OFFSET_Y = 50
};

#endif /* ENUMS_H */