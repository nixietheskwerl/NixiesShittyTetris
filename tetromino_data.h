/**
 * @file tetromino_data.h
 */

#include <cstdint>

#ifndef PIECES_H
#define PIECES_H

typedef const uint8_t tetromino_data_t;

/* Shape I */
tetromino_data_t I[16] = {
  /* Rotation 0: */
  0b0000,
  0b1111, 
  0b0000,
  0b0000,
  
  /* Rotation 1: */
  0b0100,
  0b0100,
  0b0100,
  0b0100,

  /* Rotation 2: */
  0b0000,
  0b1111,
  0b0000,
  0b0000,

  /* Rotation 3: */
  0b0100,
  0b0100,
  0b0100,
  0b0100
};

/* Shape J */
tetromino_data_t J[16] = {
  /* Rotation 0: */
  0b0000,
  0b1110,
  0b0010, 
  0b0000,
  
  /* Rotation 1: */
  0b0100,
  0b0100,
  0b1100,
  0b0000,

  /* Rotation 2: */
  0b1000,
  0b1110,
  0b0000,
  0b0000,

  /* Rotation 3: */
  0b0110,
  0b0100,
  0b0100,
  0b0000  
};

/* Shape L */
tetromino_data_t L[16] = {  
  /* Rotation 0: */
  0b0000,
  0b1110, 
  0b1000, 
  0b0000,
  
  /* Rotation 1: */
  0b1100,
  0b0100,
  0b0100,
  0b0000,

  /* Rotation 2: */
  0b0010,
  0b1110,
  0b0000,
  0b0000,

  /* Rotation 3: */
  0b0100,
  0b0100,
  0b0110,
  0b0000
};

/* Shape O */
tetromino_data_t O[16] = { 
  0b0000, 
  0b0110,
  0b0110, 
  0b0000,

  0b0000, 
  0b0110,
  0b0110, 
  0b0000,

  0b0000, 
  0b0110,
  0b0110, 
  0b0000,

  0b0000, 
  0b0110,
  0b0110, 
  0b0000,
};

tetromino_data_t S[16] = {
  /* Rotation 0: */
  0b0000,
  0b0110,
  0b1100,
  0b0000,

  /* Rotation 1: */
  0b1000,
  0b1100,
  0b0100,
  0b0000,

  /* Rotation 2: */
  0b0000,
  0b0110,
  0b1100,
  0b0000,

  /* Rotation 3: */
  0b1000,
  0b1100,
  0b0100,
  0b0000
};

/* Shape T */
tetromino_data_t T[16] = {
  /* Rotation 0: */
  0b0000,
  0b1110,
  0b0100,
  0b0000,

  /* Rotation 1: */
  0b0100,
  0b1100,
  0b0100,
  0b0000,

  /* Rotation 2: */
  0b0100,
  0b1110,
  0b0000,
  0b0000,

  /* Rotation 3: */
  0b0100,
  0b0110,
  0b0100,
  0b0000
};

/* Shape Z */
tetromino_data_t Z[16] = {
  /* Rotation 0: */
  0b0000, 
  0b1100, 
  0b0110, 
  0b0000,

  /* Rotation 1: */
  0b0100,
  0b1100,
  0b1000,
  0b0000,

  /* Rotation 2: */
  0b0000,
  0b1100,
  0b0110,
  0b0000,

  /* Rotation 3: */
  0b0100,
  0b1100,
  0b1000,
  0b0000
};

#endif