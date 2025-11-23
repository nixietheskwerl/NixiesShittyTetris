/**
 * @file playfield.cpp
 */

#include "playfield.h"

Playfield::Playfield()
{
}

void Playfield::initialize()
{
    for (uint8_t x = 0; x < GRID_WIDTH; ++x) {
        for (uint8_t y = 0; y < GRID_HEIGHT; ++y) {
            grid[x][y] = false;
        }
    }
    _is_initialized = true;
}

bool Playfield::place_tetromino()
{
    if (active_tetromino != nullptr) {
        /* Lock piece into the grid */
         for (uint8_t row = 0; row < 4; ++row) {
            uint8_t row_data = active_tetromino->get_shape(active_tetromino->get_rotation())[row];
            for (uint8_t col = 0; col < 4; ++col) {
                if ((row_data & (0b1000 >> col)) != 0) {
                    uint8_t grid_x = active_tetromino->get_x()[0] + col;
                    uint8_t grid_y = active_tetromino->get_y()[0] + row;
                    if (grid_x < GRID_WIDTH && grid_y < GRID_HEIGHT) {
                        grid[grid_x][grid_y] = true;
                    }
                }
            }
        }
        delete active_tetromino;
        active_tetromino = nullptr;
        clear_lines();
    }
    
    /* Move future tetromino to active */
    if (future_tetromino != nullptr) {
        active_tetromino = future_tetromino;
        active_tetromino->set_x(GRID_WIDTH / 2 - 2);
        active_tetromino->set_y(0);
        future_tetromino = nullptr;
    } else {
        active_tetromino = new Tetromino();
        active_tetromino->set_x(GRID_WIDTH / 2 - 2);
        active_tetromino->set_y(0);
    }
    
    /* Create a new future tetromino */
    future_tetromino = new Tetromino();
    
    /* Check for collisions on the grid */
    auto shape = active_tetromino->get_shape(active_tetromino->get_rotation());
    for (uint8_t row = 0; row < 4; ++row) {
        uint8_t row_data = shape[row];
        for (uint8_t col = 0; col < 4; ++col) {
            if ((row_data & (0b1000 >> col)) != 0) {
                uint8_t grid_x = active_tetromino->get_x()[0] + col;
                uint8_t grid_y = active_tetromino->get_y()[0] + row;
                if (grid_x >= GRID_WIDTH || grid_y >= GRID_HEIGHT || grid[grid_x][grid_y]) {
                    return false; /* Collision detected, game over. */
                }
            }
        }
    }
    return true;
}

bool Playfield::check_collision(Tetromino& tetromino, Direction direction) 
{
    if (direction == Direction::ROTATION_LEFT || direction == Direction::ROTATION_RIGHT) {
        /* Calculate and apply trial rotation */
        int curr_rotation = tetromino.get_rotation();
        int trial_rotation = curr_rotation;
        if (direction == Direction::ROTATION_RIGHT) {
            trial_rotation++;
            if (trial_rotation > 3) {
                trial_rotation = 0;
            }
        } else {
            if (trial_rotation == 0) {
                trial_rotation = 3;
            } else {
                trial_rotation--;
            }
        }
        /* Get shape at trial rotation */
        auto trial_shape = tetromino.get_shape(trial_rotation);
        
        /* Check boundaries and collisions */
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                if ((trial_shape[row] & (0b1000 >> col)) != 0) {
                    int grid_x = *tetromino.get_x() + col;
                    int grid_y = *tetromino.get_y() + row;
                    
                    /* Check boundaries and existing blocks */
                    if (grid_x < 0 || grid_x >= GRID_WIDTH ||
                        grid_y < 0 || grid_y >= GRID_HEIGHT ||
                        grid[grid_x][grid_y]) {
                        return true; // Collision found
                    }
                }
            }
        }
        return false;
    }
    else if (direction == Direction::LEFT || direction == Direction::RIGHT || direction == Direction::DOWN) {
        int delta_x = 0;
        int delta_y = 0;
        if (direction == Direction::LEFT) {
            delta_x = -1;
        } else if (direction == Direction::RIGHT) {
            delta_x = 1;
        } else if (direction == Direction::DOWN) {
            delta_y = 1;
        }

        /* Get current shape */
        auto shape = tetromino.get_shape(tetromino.get_rotation());

        /* Check for collisions in the intended direction */
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                if ((shape[row] & (0b1000 >> col)) != 0) {
                    int grid_x = *tetromino.get_x() + col + delta_x;
                    int grid_y = *tetromino.get_y() + row + delta_y;

                    /* Check boundaries and existing blocks */
                    if (grid_x < 0 || grid_x >= GRID_WIDTH ||
                        grid_y < 0 || grid_y >= GRID_HEIGHT ||
                        grid[grid_x][grid_y]) {
                        return true; // Collision found
                    }
                }
            }
        }
        return false;
    }
    return false;
}

void Playfield::clear_lines()
{
    /* Check each row for completeness and clear if full, then shift above rows down */
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        bool line_full = true;
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (!grid[x][y]) {
                line_full = false;
                break;
            }
        }
        if (line_full) {
            /* Clear the line and shift everything above down */
            for (int yy = y; yy > 0; --yy) {
                for (int x = 0; x < GRID_WIDTH; ++x) {
                    grid[x][yy] = grid[x][yy - 1];
                }
            }
            /* Clear the top line */
            for (int x = 0; x < GRID_WIDTH; ++x) {
                grid[x][0] = false;
            }
        }
    }
}