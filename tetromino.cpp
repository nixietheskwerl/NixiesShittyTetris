/**
 * @file tetromino.cpp
 */

#include "tetromino.h"

Tetromino::Tetromino(tetromino_data_t* tetromino_data)
{
    _tetromino_data = tetromino_data;
    if (_tetromino_data == nullptr) {
        _tetromino_data = get_random_shape_data();
    }
    _rotation = 0;
    x = 0;
    y = 0;
    id = 0;
}

const tetromino_data_t* Tetromino::get_random_shape_data(int seed)
{
    static std::array<tetromino_data_t*, 7> all_shapes = { I, J, L, O, S, T, Z };
    std::mt19937 rng(seed ? seed : std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, all_shapes.size() - 1);
    return all_shapes[dist(rng)];
}

void Tetromino::load_shape_data(const tetromino_data_t* tetromino_data)
{
    _tetromino_data = tetromino_data;
    _rotation = 0;
    x = 0;
    y = 0;
}