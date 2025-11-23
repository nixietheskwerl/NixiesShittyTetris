/**
 * @file tetromino.h
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <cstdint>
#include <array>
#include <random>
#include "tetromino_data.h"

class Tetromino
{
public:
    Tetromino(tetromino_data_t *tetromino_data = nullptr);
    void rotate_right()
    {
        set_rotation(_rotation + 1); /* Clockwise: 0->1->2->3->0 */
        if (_rotation > 3)
            _rotation = 0;
    }
    void rotate_left()
    {
        if (_rotation == 0)
        {
            set_rotation(3);
        }
        else
        {
            set_rotation(_rotation - 1);
        }
    }
    void set_rotation(uint8_t r) { _rotation = r; }
    int get_rotation() { return _rotation; }
    void load_shape_data(const tetromino_data_t *tetromino_data);
    std::array<std::remove_const_t<tetromino_data_t>, 4> get_shape(int rotation)
    {
        std::array<std::remove_const_t<tetromino_data_t>, 4> shape{};
        for (int i = 0; i < 4; ++i)
        {
            shape[i] = _tetromino_data[rotation * 4 + i];
        }
        return shape;
    }
    int *get_x() { return &x; }
    void set_x(int _x) { x = _x; }
    int *get_y() { return &y; }
    void set_y(int _y) { y = _y; }

private:
    tetromino_data_t *_tetromino_data = nullptr;
    tetromino_data_t *get_random_shape_data(int seed = 0);
    int _rotation; /* Current rotation state (0-3) */
    int x;
    int y;
    int id;
};

#endif /* SHAPE_H */