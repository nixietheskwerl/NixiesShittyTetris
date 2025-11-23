/**
 * @file playfield.h
 * @brief Manages the grid and piece placement.
 */

#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <cstdint>
#include <array>
#include "tetromino_data.h"
#include "tetromino.h"
#include "enums.h"

class Playfield {
public:
    Playfield();
    ~Playfield() {
        if (active_tetromino != nullptr) {
            delete active_tetromino;
            active_tetromino = nullptr;
        }
        if (future_tetromino != nullptr) {
            delete future_tetromino;
            future_tetromino = nullptr;
        }
    }
    void initialize();
    bool place_tetromino();
    void clear_lines();
    int get_width() const { return GRID_WIDTH; }
    int get_height() const { return GRID_HEIGHT; }
    bool is_initialized() const { return _is_initialized; }
    Tetromino* get_active_tetromino() const { return active_tetromino; }
    Tetromino* get_future_tetromino() const { return future_tetromino; }
    bool check_collision(Tetromino& tetromino, Direction direction);
    bool get_cell(int x, int y) const {
        if (x < GRID_WIDTH && y < GRID_HEIGHT) {
            return grid[x][y];
        }
        return false;
    }

private:
    std::array<std::array<bool, GRID_HEIGHT>, GRID_WIDTH> grid = {};
    bool _is_initialized = false;
    Tetromino* active_tetromino = nullptr;
    Tetromino* future_tetromino = nullptr;
    bool try_position(Tetromino& tetromino, int test_x, int test_y, int test_rotation);

};
#endif /* PLAYFIELD_H */